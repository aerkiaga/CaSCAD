extern char *get_empty_string();
extern char *append_string(char *dst, const char *src);
extern char *encode_utf8_escape(const char *escape);
extern char *path_basename(const char *path);
extern char *path_dirname(const char *path);
extern char *path_realpath(const char *path);
extern const char *path_extension(const char *path);
