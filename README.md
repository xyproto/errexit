# errexit

Instead of doing this in a script:

```bash
if something; then
  echo 'error: something went wrong' >&2
  exit 1
fi
```

It is possible to use `errexit`:

```bash
something || errexit -e 'something went wrong' 1
```

### General info

* Version: 1.0.0
* License: BSD-3
* Author: Alexander F. Rødseth <xyproto@archlinux.org>
