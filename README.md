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
false || errexit 'error: message'
```

Or just:

```bash
false || errexit -e 'message'
```

This will print `error: message` to `stderr`, send `SIGPIPE` to the parent process and exit with error code `141`.

### Code

This is the main thing that `errexit` is doing:

```c
fprintf(stderr, "%s%s\n", prefix, message);
pid_t ppid = getppid();
if (ppid > 1) {
    if (kill(ppid, SIGPIPE) != 0) {
        kill(ppid, SIGKILL);
    }
}
```

### Installation

```
make
sudo PREFIX=/usr/local make install
```

### General info

* Version: 1.0.0
* License: BSD-3
* Author: Alexander F. Rødseth &gt;xyproto@archlinux.org&lt;
