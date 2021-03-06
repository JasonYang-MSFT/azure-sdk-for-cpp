// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include "gtest/gtest.h"
#include <azure.hpp>
#include <string>

TEST(String, invariantCompare)
{
  using Azure::Core::Details::LocaleInvariantCaseInsensitiveEqual;
  EXPECT_TRUE(LocaleInvariantCaseInsensitiveEqual("", ""));
  EXPECT_TRUE(LocaleInvariantCaseInsensitiveEqual("a", "a"));
  EXPECT_TRUE(LocaleInvariantCaseInsensitiveEqual("a", "A"));
  EXPECT_TRUE(LocaleInvariantCaseInsensitiveEqual("aa", "AA"));
  EXPECT_TRUE(LocaleInvariantCaseInsensitiveEqual("aA", "AA"));
  EXPECT_TRUE(LocaleInvariantCaseInsensitiveEqual("abc", "ABC"));
  EXPECT_FALSE(LocaleInvariantCaseInsensitiveEqual("", "a"));
  EXPECT_FALSE(LocaleInvariantCaseInsensitiveEqual("a", ""));
  EXPECT_FALSE(LocaleInvariantCaseInsensitiveEqual("a", "aA"));
  EXPECT_FALSE(LocaleInvariantCaseInsensitiveEqual("abc", "abcd"));
}

TEST(String, toLower)
{
  using Azure::Core::Details::ToLower;
  EXPECT_TRUE(ToLower("") == "");
  EXPECT_TRUE(ToLower("a") == "a");
  EXPECT_TRUE(ToLower("A") == "a");
  EXPECT_TRUE(ToLower("AA") == "aa");
  EXPECT_TRUE(ToLower("aA") == "aa");
  EXPECT_TRUE(ToLower("ABC") == "abc");
  EXPECT_TRUE(ToLower("ABC-1-,!@#$%^&*()_+=ABC") == "abc-1-,!@#$%^&*()_+=abc");
  EXPECT_FALSE(ToLower("") == "a");
  EXPECT_FALSE(ToLower("a") == "");
  EXPECT_FALSE(ToLower("a") == "aA");
  EXPECT_FALSE(ToLower("abc") == "abcd");
}
