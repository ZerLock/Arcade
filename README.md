# Arcade

2nd project of the OOP (Oriented Object Programming) cursus.

The goal of the project was to recreate an arcade terminal by being able to change the graphic library and the game at runtime without the program stopping.

## Installation

```
# Build all the project
make
# or
make re

# Build Core only
make core

# Build Games libraries only
make games

# Build Graphicals libraries only
make graphicals
```

## Documentation

1. There is a `arcade_documentation.pdf` file in `./doc` that explain our project architecture and explain how to add a new graphical or game library that fit with our project.
2. Generate documentation about our code
```
# Generate Doxygen documentation (./doc/html/index.html)
make docs

# Delete Doxygen documentation directory
make clean_docs
```

## Testing time!
All tests files are in `./tests` directory
```
# Generate tests binary
make unit_tests

# Generate tests binary and launch tests
make tests_run

# Generate tests binary, launch tests and view gcovr coverage result
make coverage
```

## Mainteners

- [Léo Dubosclard](https://linkedin.com/in/leo-dubosclard)
- [Maxime Dziura](https://www.linkedin.com/in/maxime-dziura-918182228/)
- [Thomas Mazaud](https://www.linkedin.com/in/thomasmazaud/)
