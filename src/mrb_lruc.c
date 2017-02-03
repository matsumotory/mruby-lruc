/*
** mrb_lruc.c - LRUC class
**
** Copyright (c) MATSUMOTO Ryosuke 2017
**
** See Copyright Notice in LICENSE
*/

#include <string.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/string.h"

/* refs: https://github.com/willcannings/C-LRU-Cache.git */
#include "lruc.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  lruc *cache;
} mrb_lruc_data;

static void mrb_lruc_data_free(mrb_state *mrb, void *p)
{
  mrb_lruc_data *data = (mrb_lruc_data *)p;

  if (data->cache && lruc_free(data->cache)) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "lruc_free failed");
  }

  mrb_free(mrb, data);
}

static const struct mrb_data_type mrb_lruc_data_type = {
    "mrb_lruc_data", mrb_lruc_data_free,
};

static mrb_value mrb_lruc_init(mrb_state *mrb, mrb_value self)
{
  mrb_lruc_data *data;
  mrb_int max_size, avg_size;
  lruc *cache;

  data = (mrb_lruc_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_lruc_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "ii", &max_size, &avg_size);

  data = (mrb_lruc_data *)mrb_malloc(mrb, sizeof(mrb_lruc_data));
  if (data == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "mrb_malloc failed");
  }

  cache = lruc_new(max_size, avg_size);
  data->cache = cache;

  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_lruc_set(mrb_state *mrb, mrb_value self)
{
  mrb_lruc_data *data = DATA_PTR(self);
  mrb_value key, val;

  mrb_get_args(mrb, "oo", &key, &val);

  if (lruc_set(data->cache, strdup(RSTRING_PTR(key)), RSTRING_LEN(key), strdup(RSTRING_PTR(val)), RSTRING_LEN(val))) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "lruc_set failed");
  }

  return val;
}

static mrb_value mrb_lruc_get(mrb_state *mrb, mrb_value self)
{
  mrb_lruc_data *data = DATA_PTR(self);
  mrb_value key;
  char *val;

  mrb_get_args(mrb, "o", &key);

  lruc_get(data->cache, RSTRING_PTR(key), RSTRING_LEN(key), (void **)(&val));

  return (val) ? mrb_str_new_cstr(mrb, val) : mrb_nil_value();
}

static mrb_value mrb_lruc_delete(mrb_state *mrb, mrb_value self)
{
  mrb_lruc_data *data = DATA_PTR(self);
  mrb_value key;

  mrb_get_args(mrb, "o", &key);

  if (lruc_delete(data->cache, RSTRING_PTR(key), RSTRING_LEN(key))) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "lruc_delete failed");
  }

  return key;
}

static mrb_value mrb_lruc_free(mrb_state *mrb, mrb_value self)
{
  mrb_lruc_data *data = DATA_PTR(self);

  if (data->cache && lruc_free(data->cache)) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "lruc_delete failed");
  }

  data->cache = NULL;

  return mrb_nil_value();
}

void mrb_mruby_lruc_gem_init(mrb_state *mrb)
{
  struct RClass *lruc;
  lruc = mrb_define_class(mrb, "LRUC", mrb->object_class);
  MRB_SET_INSTANCE_TT(lruc, MRB_TT_DATA);

  mrb_define_method(mrb, lruc, "initialize", mrb_lruc_init, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, lruc, "set", mrb_lruc_set, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, lruc, "[]=", mrb_lruc_set, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, lruc, "get", mrb_lruc_get, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, lruc, "[]", mrb_lruc_get, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, lruc, "delete", mrb_lruc_delete, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, lruc, "free", mrb_lruc_free, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_lruc_gem_final(mrb_state *mrb)
{
}
