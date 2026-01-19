# Silly Notes

## DZLink

- So far, every time I have to count actors I'm using a `u8` because
  I don't think that I'll need more that 255 actors. In the future,
  if I ever plan on passing that count, I should switch from a `u8`
  so something more appropriate.


## HackerOoT

- The macro `DEFINE_ACTOR` takes 3 arguments: an actor name (ex. ActorExample),
  an actor name but *more professional* (ex. actor_example) which might
  be sufixed by `dz_` to mark it as part of this DZ project like ZeldaOoT does.
  And finally, an enum value to name the actor's id.
  That's nice and all but the second *professional* value isn't used, because
  in ZeldaOoT it's used for some spec stuff related to ROM memory or compilation
  or idk. Because my code-base is simple so far ([16/01/2026]) I don't really
  require that kind of argument for the macro. But I will keep it in case
  it becomes handy later.

## Libdragon

- `dfs_close` should only be used to close files; not to "un-initialize"
  the file system. I though it was the opposite of `dfs_init` and did
  this:
  ```c
  dfs_close(DFS_DEFAULT_LOCATION);
  ```
  But this crashes the game. Be careful folks.
