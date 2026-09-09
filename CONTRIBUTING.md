# Contributing to SPY

Thank you for your interest in SPY. Bug reports, documentation fixes, a compiler or an instruction
set we do not detect yet, and whole new axes of detection are all welcome.

By opening a pull request you agree to license your contribution under the
[Boost Software License 1.0](LICENSE.md), like the rest of the project, and confirm you have the
right to do so. Everyone taking part is expected to follow the
[Code of Conduct](CODE_OF_CONDUCT.md).

Bugs and feature requests go through the [issue templates](.github/ISSUE_TEMPLATE). Everything
below is about patches.

If anything below is unclear, or you would rather talk an idea through before writing it, come
and ask on [our Discord](https://discord.gg/a9qVaEMeXd8). No question is too small, and a five
minute conversation there often saves a rewrite.

## Generative AI

We will not ask whether a patch was written with a language model, and we would be badly placed
to: parts of this project's own infrastructure were. **What gets reviewed is the patch, not how
the characters arrived.**

That cuts both ways. A pull request nobody has read is a review request pointed at us rather than
a contribution, and reading generated code costs more than writing the thing by hand.
Concretely:

- **answer the issue, not its checklist.** A patch that satisfies every word of a report while
  missing what it was asked for is a rewrite waiting to happen, and it is the failure mode a
  model falls into first. Here that means testing past the machine on your desk: SPY answers a
  different question on every compiler and every architecture, and the CI cross-builds for the
  ones you do not own. Covering only some of them is fine as long as you say which, and asking
  for help with the rest is fine too
- **send only what you have read and can explain.** "That is what the model produced" is not an
  answer to a review comment, and a branch its author cannot defend is closed rather than
  iterated on
- **a detection arrives with a test that fails without it.** A model will happily produce tests
  that pass against any implementation, wrong ones included; those are worth less than no tests
  at all, because they look like coverage
- **build it and run the suite before opening the pull request**, as described further down. An
  unbuilt patch is noise rather than a draft
- **opening pull requests in bulk is spam**, and it gets you blocked from the repository without
  discussion

None of this is about the tool. The same pull request typed by hand is closed just as fast.

## Courses and hackathons

Some of you arrive here because a course, a hackathon or a seasonal event asks for a number of
merged pull requests. **You are welcome.** A student who wants to see how a library answers
questions about the machine it compiles on is exactly who we wrote this for, and nobody is going to
hold a deadline against you.

What does not work is the shape those events push you into. A quota counts pull requests, so it
rewards volume, and volume is the one thing a small maintainer team cannot absorb. A batch of
whitespace fixes, README typos or reformatted headers costs more attention than it saves anyone,
and it buries the reports we actually need to read. Those get closed, and **it is the format's
fault rather than yours**.

So say so. In the issue, or on [Discord](https://discord.gg/a9qVaEMeXd8): "I have two weeks and I
would like to land something real" is a message we answer gladly, and we will point you at
something that fits the time you have. The
[good first issue](https://github.com/jfalcou/spy/labels/good%20first%20issue) label lists work
that is genuinely open, sized for a newcomer and worth having. One of those, with questions asked
along the way, will teach you more and stands a far better chance of being merged than ten
cosmetic patches.

The line between the two is intent, and it is usually plain to see: someone who asks questions
gets answers, an account opening the same patch across thirty repositories gets blocked.

## Building and running the tests

Everything goes through CMake presets, one per configuration the CI runs:

```bash
cmake --preset gcc
cmake --build build/gcc --target unit.compiler.exe
ctest --preset gcc -R compiler
```

**One target per test file**, so `test/unit/compiler.cpp` builds as `unit.compiler.exe`, and that
is the loop you want while working on a detection. `unit.exe` builds the whole suite, `samples.exe`
the documentation examples, and `cmake --list-presets` gives every configuration, from `clang` to
`gcc-aarch64-sve2`, `wasm` and `mingw64`.

**A test that only holds in Debug is not a test.** The matrix builds Debug and Release, `NDEBUG` is
defined in Release, and `assert` disappears with it. An assertion that must hold in both is written
`static_assert`.

## Adding a detection

Every axis has the same shape, and a new detection follows it:

- a value in the vendor `enum class` in `spy::_`, **at the end of the list**, since renumbering
  changes what comparisons answer for everyone who already compiled;
- an `xxx_info<Vendor, M, N, P>` carrying `vendor` and `version`;
- an alias `xxx_t` per vendor in `spy::_`, and a bare instance in `spy` with a trailing underscore,
  `gcc_`, `msvc_`, at version `-1, 0, 0`, which means "that vendor, whatever its version";
- the `#if` branch that produces it, **placed before the chains it derives from**: Clang-CL before
  MSVC and before clang, MinGW before `__GNUC__`;
- the `operator""_<name>` literal, with its `@ingroup api` and its `@brief`;
- the row in the documentation table of the object that carries the result;
- the other compiler lists in the library, `sanitizers.hpp` first;
- the branch in the matching unit test, asserting the expected value and the falseness of every
  other one;
- the changelog entry, with `[BREAKING CHANGE]` when an existing chain changes its answer.

A toolchain is reported as itself, never as the one it derives from: Clang-CL is `spy::clangcl_`,
MinGW is `spy::mingw32_` or `spy::mingw64_`. A guard written on `spy::gcc_` therefore does not cover
MinGW, which is why the lists elsewhere in the library have to be reread when a vendor appears.

## Documentation

A public value carries a doxygen block framed by two lines of `=` drawn to column 100, with
`@ingroup api`, a `@brief`, the description, and a `@godbolt{samples/<name>.cpp}` pointing at a real
file of `test/samples`. Tables of supported values give the exact name, trailing underscore
included, and a `@ref` to a neighbour is written fully qualified.

A value that depends on the platform puts its block in a branch of its own, between the real
detection and its default:

```cpp
#if defined(SPY_SUPPORTS_FP16_TYPE)
  constexpr inline bool type = true;
#elif defined(SPY_DOXYGEN_INVOKED)
  //! the @ingroup api block
  constexpr inline bool type = _::implementation_defined {};
#else
  constexpr inline bool type = false;
#endif
```

`_::implementation_defined` exists in no compiled code: it is a name doxygen prints where a bare
`true` or `false` would mean nothing on a page.

## Tests

Two directories, both globbed by CMake, so dropping a `.cpp` in either is enough:

- `test/unit/*.cpp`, one file per axis. A test is a `main` that prints what it checks and then
  asserts it, with `#if` branches saying what each platform must answer;
- `test/samples/*.cpp`, the examples the documentation shows through `@godbolt`. They are compiled
  and run like the rest, so a wrong example fails the CI.

## Other kinds of change

A patch more often takes one of these shapes:

**A wrong answer.** The fix and its test in the same commit, the new case added to the unit file
that already covers the axis, next to the cases that did not catch it. Write the case first and
watch it fail: a regression test that was never red proves nothing.

**A new vendor or version on an existing axis.** The checklist above, minus the parts that already
exist. What is easy to forget is the ordering of the `#if` chain and the lists elsewhere in the
library.

**Documentation alone.** Still code: an example under `test/samples/` is compiled and run by the CI
like any other file, and the `spy-doxygen` target has to stay silent.

**Infrastructure, CMake, the CI workflows, the presets.** There is no unit test to write, so the
pull request body carries the weight. Say what changes for someone building the project, and
whether an existing build directory keeps working.

**An issue rather than a patch.** A wrong detection is only actionable with the compiler and its
version, the target triple, and the command line. A Godbolt link that reproduces it replaces all
three.

**Work on an open issue.** The [open issues](https://github.com/jfalcou/spy/issues) are all fair
game, and help on any of them is welcome. Say on the issue that you are taking it, so that two
people do not write the same patch.

**Anything else.** Ideas outside this list are welcome too. Bring one up on
[Discord](https://discord.gg/a9qVaEMeXd8) before you write it: a design that has been talked
through lands, and one that has not tends to need rewriting once it arrives.

## Before you push

Build and run the tests for what you touched, then the documentation:

```bash
ctest --preset gcc --output-on-failure -R compiler
cmake --build build/gcc --target spy-doxygen
```

The doxygen target must stay silent: a warning here is a broken link on the website.

Everything committed here is in English, comments and doxygen included. One line checks it:

```bash
grep -nP '^\s*//.*[éèêàçùôûîïœ]' <the files you touched>
```

Formatting is `pre-commit`, installed once by the hooks the project sets up and run in the CI by
the `Meta Checks` job, so a reformatted file never lands as a surprise in a review.

If your change touches an architecture you cannot boot, say so in the pull request and let the CI
answer: it cross-builds and runs aarch64, SVE, PowerPC, RISC-V, WebAssembly and the Windows
toolchains.

## Commits and pull requests

**Commit titles are one short imperative line.** No body unless the change is genuinely not
obvious, and then a few sentences of prose rather than a bulleted report.

Branches are `issue-<n>/<short-description>` for a tracked issue, or a short explicit name
otherwise. Titles for a tracked fix read `Fix #<n> - short description`.

Pull request descriptions are plain prose, as long as the "why" requires and no longer. No section
headers, no test plan, no restating the issue number that is already in the title.
