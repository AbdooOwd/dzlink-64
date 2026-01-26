# DZ Link

This is my first attempt at making a 3D game for the Nintendo 64 using
[libdragon](https://libdragon.dev/) and [Tiny3D](https://github.com/HailToDodongo/Tiny3D).

## Table of Contents

* [Usage Condition (important!!!)](#️-usage-conditions)
* [How to Build](#how-to-build)


## ☪️ Usage Conditions

I developed this engine as a Muslim to explore N64 architecture,
3D graphics, mathematics, and game development concepts.

With that in mind, I ask anyone **using** or **learning** from this code
to respect this simple condition:
<u>Please do **NOT** apply this knowledge to create anything
that contradicts Islamic ethics</u>.

This includes (but isn't limited to):
- ❌ Games with musical audio
- ❌ Depictions of human/animal faces/figures
- ❌ Gambling mechanics or promotion
- ❌ Relationships outside of marriage like dating
- ❌ Content promoting other haram activities

If you're not Muslim, that's OK! I'm not asking you to share
my beliefs, but to respect them.

**Think of it like this:**
If a vegetarian shares his recipe, he'd reasonably ask
you not to use it for meat dishes. Similarly, I'm asking
you not to use my work for prohibited content.

If you're looking for some code to learn from for your game
while you have the intention of adding Islamically prohibited
stuff; then please look for another repo.

### Why these restrictions?

In Islam, I'm accountable not just for what I make & share,
but also for how my projects & works are used. I'm sharing my work
to provide useful documentation to understand the N64's limitations
and the knowledge it leads to.

**Respecting these conditions is fundamental to using this engine.**

> *"Whoever guides someone to goodness will have a reward like the one who did it."*
> <br/> – Prophet Muhammad (peace be upon him)


## How to build

You'll require [libdragon](https://libdragon.dev/) for an N64 library/interface
and [Tiny3D](https://github.com/HailToDodongo/Tiny3D) for a nice microcode
to handle 3D stuff (I still don't quite understand all of that yet).

The [`Makefile`](./Makefile) is the file that is used to manipulate
the project (build, clean, run...) using [`make`](https://www.gnu.org/software/make/)
(see it as... build automation? like a bash script but better).

After acquiring `libdragon` and `tiny3d`, run `make` to build the project.

## How to Run

`libdragon` aims to make ROMs for real hardware. So running the produced
ROM of this project in any emulator will likely not work.
It will, though, work on `ares` as this is the one I use to work
on this project.
You could also try [Gopher64](https://github.com/gopher64/gopher64),
but I haven't tried it.
