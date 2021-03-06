// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <internal/contract.hpp>
#include <string>

#define AZURE_UNREFERENCED_PARAMETER(x) ((void)(x));

namespace Azure { namespace Core { namespace Details {

  bool LocaleInvariantCaseInsensitiveEqual(const std::string& lhs, const std::string& rhs) noexcept;
  std::string const ToLower(const std::string& src) noexcept;

}}} // namespace Azure::Core::Details
