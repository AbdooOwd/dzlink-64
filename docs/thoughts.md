# Todos

- [DONE] Implement an actor system (heavily inspired from HackerOoT)
- Learn how to display a 3D plane with Tiny3D
- [DONE] Learn how to display a 3D model
- Find the most efficient way to store 3D Objects:
  `.t3dm` (Tiny3D) or raw `.c` files like in ZeldaOoT.
  - If I end up choosing the second option (very improbable),
    I'll ~~definitely~~ probably would need to write my own thing
    to display 3D graphics.
- Add my `compile_flags.txt` to [`docs/`](./) for people to have correct
  includes if using clangd and maybe note some NeoVim-C stuff
  for NVim users.
- I should implement `PlayState` & `GameState` so I can handle the game loop correctly.
- Having some functions for the controller (`joypad_*` functions) is nice n' all,
  but I don't know if calling those functions every time I need some input
  is smart, efficient, and more importantly: PERFORMANT! So instead, I might
  make some `Input` type that will have the essential stuff we need.
  Or rather, all the data that those functions provide would all be neatly
  stored in one data structure. So game states or actors could store a pointer
  to that input.
- With how currently almost all my memory allocations are done through `malloc`,
  I think fragmentation is a bit more likely to happen (though I have been told
  that it's not likely to happen). I found `libdragon-extensions`'s implementation
  of a "Memory Pool" pretty interesting. It's downside though is the fact that
  after initialization; a memory pool cannot be freed. ***Memory Leak~!***
  But I have to admit that this implementation is much faster than `malloc`,
  because it reserves a space in memory using `malloc` only once
  (when initializing the memory zone). When allocating using its
  `mem_zone_alloc` function, the only thing happening is incrementing its
  position pointer by the new allocation's size. That's much cheaper than
  `malloc` especially in a game-loop when run ever frame.
  I should take inspiration from that `MemZone` implementation.
  Its best use cases are when making, for example, a pool for a maximum
  of *n* actor. But with my current implementation (actors chained with
  `next` & `prev` pointers as a doubly-linked list), actors can be allocated
  anywhere (probably...). And as long as they're not spawned every frame,
  thus using `malloc` every frame, it's not that bad! And on top of that,
  unlike the memory zone implementation, I can allocate as much actors
  as I want as long as I have enough RAM; meaning that if some level is
  very small (for example) and for some :sparkles: ***magical reasons*** :sparkles:,
  the game is currently using very little RAM, I can populate the level
  with a **LOT** of actors.
  But again, I should find a way to avoid fragmentation...
  - Maybe I could "reorganize" the memory on load times? Like, for example:
    there's some time where the player won't be bothered with some freezing
    or stuttering (for example when loading). At that time, we could
    *try* to reorganize the memory so all the free fragments and spaces
    are put to the end of memory and all allocations pushed back to leave
    no space in between. Nice idea but how do I implement such a thing?
    How is the game supposed to recognize when a space memory is free
    or if it's just some coincidentally placed zeros? Gotta think
    of a solution...
