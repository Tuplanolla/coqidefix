#include <dlfcn.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "coqidefix.h"

static gboolean (* parse)(gchar const* spec,
		GdkColor* color) = NULL;

static void load(void) {
	parse = dlsym(RTLD_NEXT,
			/* libgdk-x11-2.0.so: */ "gdk_color_parse");
	if (parse == NULL) {
		fputs(dlerror(), stderr);
		fputc('\n', stderr);
	}
}

static gboolean affected(gchar const* const spec,
		GdkColor const* const color) {
	size_t index;

	for (index = 0;
			index < sizeof skips / sizeof *skips;
			++index) {
		struct skip const* skip;

		skip = &skips[index];

		if (skip->parsed) {
			if (skip->match.after.red == color->red
					&& skip->match.after.green == color->green
					&& skip->match.after.blue == color->blue)
				return FALSE;
		} else {
			int (* cmp)(char const* s1,
					char const* s2);

			cmp = skip->match.before.ignore_case ? strcmp : strcasecmp;

			if (cmp(skip->match.before.spec, spec) == 0)
				return FALSE;
		}
	}

	return TRUE;
}

static void change(GdkColor* const color) {
	color->red = G_MAXUINT16 - color->red;
	color->green = G_MAXUINT16 - color->green;
	color->blue = G_MAXUINT16 - color->blue;
}

gboolean gdk_color_parse(gchar const* const spec,
		GdkColor* const color) {
	gboolean succeeded;

	if (parse == NULL)
		load();

	succeeded = parse(spec, color);

	trace(stderr, "gdk_color_parse(\"%s\")", spec);

	if (!succeeded)
		goto end;

	trace(stderr, " = {%d, %d, %d}",
			color->red, color->green, color->blue);

	if (!affected(spec, color))
		goto end;

	change(color);

	trace(stderr, " -> {%d, %d, %d}",
			color->red, color->green, color->blue);

end:
	trace(stderr, "\n");

	return succeeded;
}
