// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * Copyright (C) 2021-2023 Cyril Hrubis <metan@ucw.cz>
 */

/*
 * C struct to JSON serializer and deserializer.
 */

#ifndef GP_JSON_SERDES_H
#define GP_JSON_SERDES_H

#include <stddef.h>
#include <stdint.h>

enum json_serdes_type {
	GP_JSON_SERDES_STR,
	GP_JSON_SERDES_UINT,
	GP_JSON_SERDES_INT,

	/* parameter does not have to be present */
	GP_JSON_SERDES_OPTIONAL = 0x80,
};

#define GP_JSON_SERDES_TYPE(type) ((type) & 0x0f)

struct gp_json_int_limits {
	int64_t min;
	uint64_t max;
};

typedef struct gp_json_struct {
	const char *id; /* JSON id */
	size_t offset;  /* Offset in base struct */

	enum json_serdes_type type; /* Variable type */
	size_t type_size; /* Variable size, either explicit size or sizeof() */

	union {
		struct gp_json_int_limits lim_int;
		size_t str_max_size;
	};
} gp_json_struct;

#define GP_JSON_SERDES_STR_CPY(struct, memb, size) \
	{.id = #memb, .offset = offsetof(struct, memb),\
	 .type = GP_JSON_SERDES_STR, .type_size = size}

#define GP_JSON_SERDES_STR_DUP(struct, memb, max_size) \
	{.id = #memb, .offset = offsetof(struct, memb),\
	 .type = GP_JSON_SERDES_STR, .str_max_size = max_size}

#define GP_JSON_SERDES_INT(struct, memb, min, max) \
	{.id = #memb, .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_INT, .type_size = sizeof(int), .lim_int = {min, max}}

#define GP_JSON_SERDES_UINT(id, struct, memb, min, max) \
	{.id = #memb, .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_UINT, .type_size = sizeof(unsigned int), .lim_int = {min, max{}

#define GP_JSON_SERDES_LONG(struct, memb, min, max) \
	{.id = #memb, .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_INT, .type_size = sizeof(long), .lim_int = {min, max}}

#define GP_JSON_SERDES_ULONG(id, struct, memb, min, max) \
	{.id = #memb, .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_UINT, .type_size = sizeof(unsigned long), .lim_int = {min, max{}

#define GP_JSON_SERDES_UINT8(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_UINT, .type_size = 1, .lim_int = {min, max}}

#define GP_JSON_SERDES_INT8(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_INT, .type_size = 1, .lim_int = {min, max{}

#define GP_JSON_SERDES_UINT16(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_UINT, .type_size = 2, .lim_int = {min, max}}

#define GP_JSON_SERDES_INT16(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_INT, .type_size = 2, .lim_int = {min, max{}

#define GP_JSON_SERDES_UINT32(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_UINT, .type_size = 4, .lim_int = {min, max}}

#define GP_JSON_SERDES_INT32(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_INT, .type_size = 4, .lim_int = {min, max{}

#define GP_JSON_SERDES_UINT64(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_UINT, .type_size = 8, .lim_int = {min, max}}

#define GP_JSON_SERDES_INT64(id, struct, memb, min, max) \
	{.id = (sid), .offset = offsetof(struct, memb), \
	 .type = GP_JSON_SERDES_INT, .type_size = 8, .lim_int = {min, max}}

/**
 * @brief Deserializes a JSON object into a C structure
 *
 * Consumes and JSON object and deserializes it into a C structure.
 *
 * This function can be mixed with the rest of the JSON parser functions.
 *
 * @json A json reader.
 * @val A json reader value.
 * @desc An alphabetically sorted by id and NULL id terminatred array of
 *       structure member descriptions.
 * @baseptr A pointer to the deserialized C structure.
 */
int gp_json_read_struct(gp_json_reader *json, gp_json_val *val,
                        gp_json_struct *desc, void *baseptr);

/**
 * @brief Serializes a C structure into a JSON object
 *
 * @json A json writer
 * @desc An NULL id terminated array of structure member descriptions.
 * @id An JSON id for the object, should be NULL if there is no id required in
 *     current context, e.g. inside of an JSON array.
 * @baseptr A pointer to the serialized C structure.
 */
int gp_json_write_struct(gp_json_writer *json, gp_json_struct *desc,
                         const char *id, void *baseptr);

#endif /* GP_JSON_SERDES_H */