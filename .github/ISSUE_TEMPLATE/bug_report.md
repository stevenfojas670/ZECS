---
name: Bug report
about: Something in ZECS behaves incorrectly
title: ""
labels: bug
assignees: ""
---

## Summary

Describe the bug in one or two sentences.

## Affected class/method

e.g. `EntityManager::DestroyEntity`

## Steps to reproduce

Ideally a minimal Catch2 test case:

```cpp
TEST_CASE("...", "[Class][Method]")
{
}
```

## Expected vs actual

**Expected:**

**Actual:**

## Build config

- Configuration: Debug / Release
- Compiler and version:

## Acceptance criteria

- [ ] A regression test named per `Test/README.md` fails before the fix and passes after
