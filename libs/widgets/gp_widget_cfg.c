//SPDX-License-Identifier: LGPL-2.0-or-later

/*

   Copyright (c) 2022 Cyril Hrubis <metan@ucw.cz>

 */

#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "widgets/gp_widget_cfg.h"

char *gp_widget_cfg_path(const char *app_name, const char *cfg_filename)
{
	char *home_path, *full_path = NULL, *sep;
	size_t home_len;

	home_path = getenv("HOME");
	if (!home_path) {
		errno = ENOENT;
		return NULL;
	}

	if (home_path[0] != '/') {
		errno = EINVAL;
		return NULL;
	}

	home_len = strlen(home_path);

	sep = home_path[home_len-1] == '/' ? "" : "/";

	if (asprintf(&full_path, "%s%s.config/%s/%s", home_path, sep, app_name, cfg_filename) < 0) {
		errno = ENOMEM;
		return NULL;
	}

	return full_path;
}

int gp_widget_cfg_mkpath(const char *app_name)
{
	char *home_path;
	int home_fd, conf_fd, err;

	home_path = getenv("HOME");
	if (!home_path) {
		errno = ENOENT;
		return 1;
	}

	home_fd = open(home_path, O_DIRECTORY);
	if (home_fd < 0)
		return 1;

	if (mkdirat(home_fd, ".config", 0700)) {
		if (errno != EEXIST)
			return 1;
	}

	conf_fd = openat(home_fd, ".config", O_DIRECTORY);
	err = errno;
	close(home_fd);

	if (conf_fd < 0) {
		errno = err;
		return 1;
	}

	if (mkdirat(conf_fd, app_name, 0700)) {
		if (errno != EEXIST)
			return 1;
	}

	return 0;
}