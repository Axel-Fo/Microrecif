# MicroRécif — Life Simulation Project

C++ simulation project built around shapes, lifeforms, and a graphical interface.

**Authors:** Axel Fouet & Nestor Guibentif

---

## Build & run

```bash
make          # compile the project
make depend   # update dependencies
./projet      # run
make test     # build and run tests
```

---

## Project structure

| Module | Description |
|---|---|
| `shape` | Geometric shapes and collision detection |
| `lifeform` | Lifeform logic and behavior |
| `simulation` | File parsing and simulation state |
| `gui` / `graphic` | Graphical interface |

Tests are written in `test.cc` and allow testing each module independently.

---

## Development notes

Work was split by module across the three deliverables and coordinated via GitLab and VS Code. The hardest bug was a collision issue in `intersect()` caused by an incorrect condition when using an epsilon threshold — found using a debugger and fixed.
