#ifndef COQIDEFIX_H
#define COQIDEFIX_H

#include <gdk/gdk.h>

#ifdef TRACE
#define trace(stream, ...) (void )fprintf(stream, __VA_ARGS__)
#else
#define trace(stream, ...) (void )(stream, __VA_ARGS__)
#endif

struct skip {
	gboolean parsed;
	union {
		struct {
			gchar const* spec;
			gboolean ignore_case;
		} before;
		struct {
			guint16 red;
			guint16 green;
			guint16 blue;
		} after;
	} match;
};

static struct skip const skips[] = {
	{
		.parsed = TRUE,
		.match.before = {
			.spec = "#010101010101",
			.ignore_case = TRUE
		},
	}, {
		.parsed = TRUE,
		.match.before = {
			.spec = "#000040400000",
			.ignore_case = TRUE
		},
	}, {
		.parsed = TRUE,
		.match.before = {
			.spec = "#404000000000",
			.ignore_case = TRUE
		},
	}
};

#endif
