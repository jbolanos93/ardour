#include <glibmm/pattern.h>

#include "pbd/error.h"
#include "pbd/compose.h"
#include "pbd/file_utils.h"

#include "ardour/panner_manager.h"
#include "ardour/panner_search_path.h"

#include "i18n.h"

using namespace std;
using namespace ARDOUR;
using namespace PBD;

PannerManager* PannerManager::_instance = 0;

PannerManager::PannerManager ()
{
}

PannerManager::~PannerManager ()
{
	for (list<PannerInfo*>::iterator p = panner_info.begin(); p != panner_info.end(); ++p) {
		delete *p;
	}
}

PannerManager&
PannerManager::instance ()
{
	if (_instance == 0) {
		_instance = new PannerManager ();
	}

	return *_instance;
}

void
PannerManager::discover_panners ()
{
	vector<sys::path> panner_modules;

	Glib::PatternSpec so_extension_pattern("*.so");
	Glib::PatternSpec dylib_extension_pattern("*.dylib");

	find_matching_files_in_search_path (panner_search_path (),
	                                    so_extension_pattern, panner_modules);

	find_matching_files_in_search_path (panner_search_path (),
	                                    dylib_extension_pattern, panner_modules);

	info << string_compose (_("looking for panners in %1"), panner_search_path().to_string()) << endmsg;

	for (vector<sys::path>::iterator i = panner_modules.begin(); i != panner_modules.end(); ++i) {
		panner_discover ((*i).to_string());
	}
}
int
PannerManager::panner_discover (string path)
{
	PannerInfo* pinfo;

	if ((pinfo = get_descriptor (path)) != 0) {
		panner_info.push_back (pinfo);
		info << string_compose(_("Panner discovered: \"%1\""), pinfo->descriptor.name) << endmsg;
	}

	return 0;
}

PannerInfo*
PannerManager::get_descriptor (string path)
{
	void *module;
	PannerInfo* info = 0;
	PanPluginDescriptor *descriptor = 0;
	PanPluginDescriptor* (*dfunc)(void);
	const char *errstr;

	if ((module = dlopen (path.c_str(), RTLD_NOW)) == 0) {
		error << string_compose(_("PannerManager: cannot load module \"%1\" (%2)"), path, dlerror()) << endmsg;
		return 0;
	}

	dfunc = (PanPluginDescriptor* (*)(void)) dlsym (module, "panner_descriptor");

	if ((errstr = dlerror()) != 0) {
		error << string_compose(_("PannerManager: module \"%1\" has no descriptor function."), path) << endmsg;
		error << errstr << endmsg;
		dlclose (module);
		return 0;
	}

	descriptor = dfunc();
	if (descriptor) {
		info = new PannerInfo (*descriptor, module);
	} else {
		dlclose (module);
	}

	return info;
}

PannerInfo*
PannerManager::select_panner (ChanCount in, ChanCount out)
{
	PanPluginDescriptor* d;
	int32_t nin = in.n_audio();
	int32_t nout = out.n_audio();

	/* look for exact match first */

	for (list<PannerInfo*>::iterator p = panner_info.begin(); p != panner_info.end(); ++p) {
		d = &(*p)->descriptor;

		if (d->in == nin && d->out == nout) {
			return *p;
		}
	}

	/* no exact match, look for good fit on inputs and variable on outputs */

	for (list<PannerInfo*>::iterator p = panner_info.begin(); p != panner_info.end(); ++p) {
		d = &(*p)->descriptor;

		if (d->in == nin && d->out == -1) {
			return *p;
		}
	}

	/* no exact match, look for good fit on outputs and variable on inputs */

	for (list<PannerInfo*>::iterator p = panner_info.begin(); p != panner_info.end(); ++p) {
		d = &(*p)->descriptor;

		if (d->in == -1 && d->out == nout) {
			return *p;
		}
	}

	/* no exact match, look for variable fit on inputs and outputs */

	for (list<PannerInfo*>::iterator p = panner_info.begin(); p != panner_info.end(); ++p) {
		d = &(*p)->descriptor;

		if (d->in == -1 && d->out == -1) {
			return *p;
		}
	}

	warning << string_compose (_("no panner discovered for in/out = %1/%2"), nin, nout) << endmsg;

	return 0;
}
