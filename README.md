# errexit

Instead of doing this in a script:

```bash
if false; then
  echo 'error: message' >&2
  exit 1
fi
```

It is possible to use `errexit`:

```bash
false || errexit -e 'message'
```

This will print `error: message` to `stderr`, send `SIGPIPE` to the parent process and exit with error code `141`.

### Installation

```
make
sudo PREFIX=/usr/local make install
```

### General info

* Version: 1.0.0
* License: BSD-3
* Author: Alexander F. Rødseth <xyproto@archlinux.org>
