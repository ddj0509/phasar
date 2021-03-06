/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

#ifndef SCOPES_H_
#define SCOPES_H_

#include <iostream>
#include <map>
#include <string>

namespace psr {

enum class Scope { function, module, project };

std::ostream &operator<<(std::ostream &os, const Scope &s);

extern const std::map<std::string, Scope> StringToScope;

extern const std::map<Scope, std::string> ScopeToString;

} // namespace psr

#endif