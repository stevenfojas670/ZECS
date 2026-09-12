# ZECS Tests

Rules for writing tests in this folder. The goal is that every test name tells you
**what was done** and **what should be true afterward**, so a failing test in the
CTest output explains itself without opening the file.

## Framework & layout

- **Catch2 v3** (`Catch2::Catch2WithMain` supplies `main()`, so no test file declares one).
- One file per class under test: `<ClassName>_Tests.cpp`. Add new files to `Test/CMakeLists.txt`.
- All tests live in `namespace Tests`.
- Shared helpers (e.g. `CaptureStdout`) go in `Helpers.h`.
- `Sandbox/` is for experiments and is **exempt** from these rules.

## Naming: scenario + expected outcome

```
TEST_CASE("<scenario> <expected outcome>", "[ClassName][Method]")
```

- **Scenario:** what is done, and under what condition. Start with a gerund
  (`Inserting…`, `Removing…`, `Destroying…`) or a subject (`A destroyed handle…`).
- **Outcome:** what is observably true afterward, using a verb such as *returns*, *is*,
  *makes … return*, *is rejected*, *reuses*, *logs*.
- One present-tense sentence, with no trailing period.
- Don't put a group prefix in the name (`Insert-Tests:`). Tags do that job.
- Don't use vague words: *works*, *correctly*, *testing*, *check*, *handles*.
- Name a concrete value only when the value is the point (`generation to 2`, `NULL_INDEX`).
- Names must be unique across the test binary. Catch2 refuses to run duplicates.

### Examples

| Before | After |
|---|---|
| `Insert-Tests: Insert component into storage.` | `Inserting a component makes Has() return true` |
| `Insert-Tests: Insert more than the maximum allowable components` | `Inserting at NULL_INDEX is rejected` |
| `Insert-Tests: Random insertions` | `Removing one component from a heavily populated storage makes Has() return false` |
| `Remove-Tests: Remove a non-existent component` | `Removing a component that was never inserted leaves Has() false` |
| `Register-Tests: Two different components have two different ids` | `Registering two component types assigns them distinct ids` |
| `Detect a stale entity` | `A destroyed handle is no longer alive` |

## Tags

Every test gets exactly two tags: `[ClassName][Method]`.

- `[ClassName]` matches the file name (`ComponentStorage_Tests.cpp` → `[ComponentStorage]`).
- `[Method]` is the **one** public method whose behavior is under test, spelled exactly
  as in code (`[Insert]`, `[Remove]`, `[RegisterComponent]`, `[DestroyEntity]`, `[IsAlive]`).
  If a test calls several methods, tag the one the outcome is about.

Run a subset:

```powershell
build\bin\Debug\Test.exe "[ComponentStorage]"             # one class
build\bin\Debug\Test.exe "[ComponentStorage][Remove]"     # one method
build\bin\Debug\Test.exe --list-tests                     # see every name
ctest --preset debug -R "Removing"                        # by name via CTest
```

## Test body

- **Arrange / Act / Assert**, with a blank line between the three blocks.
- **One behavior per test.** Several `REQUIRE`s describing the same resulting state are
  fine. If the *name* needs "and" to join two unrelated outcomes, split it into two tests.
- `REQUIRE` by default. Use `CHECK` only when later assertions are still meaningful after a failure.
- Every test has at least one assertion. Don't just print to the console. If output is the
  behavior, capture it with `CaptureStdout` and assert on it.
- Define component structs **locally inside the test** (`struct Health { int value; };`).
- Heap-allocate managers and storages with `std::make_unique`. They embed arrays of
  65536 elements, which is too large for the default 1 MB stack.
- When an expected value isn't obvious (wraparound, sentinel values, free-list order),
  add a one-line comment saying why.

## Checklist for a new test

- [ ] Name states the scenario **and** the expected outcome
- [ ] Tagged `[ClassName][Method]`
- [ ] New file added to `Test/CMakeLists.txt`
- [ ] At least one assertion
- [ ] Passes when run alone via its tag filter
