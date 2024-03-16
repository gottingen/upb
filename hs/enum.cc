// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// http://code.google.com/p/protobuf/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: kenton@google.com (Kenton Varda)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

// Copyright (c) 2008-2013, Dave Benson.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Modified to implement C code by Dave Benson.

#include <google/protobuf/io/printer.h>
#include <hs/enum.h>
#include <hs/helpers.h>

#include <map>
#include <set>

namespace google::protobuf::compiler::hs {

EnumGenerator::EnumGenerator(const EnumDescriptor* descriptor,
                             const std::string& dllexport_decl)
    : descriptor_(descriptor), dllexport_decl_(dllexport_decl) {}

EnumGenerator::~EnumGenerator() {}

void EnumGenerator::GenerateDefinition(io::Printer* printer) {
  std::map<std::string, std::string> vars;
  vars["classname"] =
      FullNameToC(descriptor_->full_name(), descriptor_->file());
  vars["shortname"] = descriptor_->name();
  vars["uc_name"] =
      FullNameToUpper(descriptor_->full_name(), descriptor_->file());

  SourceLocation sourceLoc;
  descriptor_->GetSourceLocation(&sourceLoc);
  PrintComment(printer, sourceLoc.leading_comments);

  printer->Print(vars, "class Enum_$shortname$:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("value = 0\n\n");
  printer->Print("def __init__(self, value: int):\n");
  printer->Indent();
  printer->Indent();
  printer->Print("self.value = value\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print("def __str__(self) -> str:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("return str(self.value)\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print(vars, "def __eq__(self, other: Enum_$shortname$) -> bool:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("return self.value == other.value\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print("def __eq__(self, other: int) -> bool:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("return self.value == other\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print("def __hash__(self) -> int:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("return hash(self.value)\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print("def __int__(self) -> int:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("return self.value\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print("def __repr__(self) -> str:\n");
  printer->Indent();
  printer->Indent();
  printer->Print(vars, "return f'Enum_$shortname$({self.value})'\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print("def __setitem__(self, value: int) -> None:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("self.value = value\n");
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n");
  printer->Print("def __getitem__(self) -> int:\n");
  printer->Indent();
  printer->Indent();
  printer->Print("return self.value\n");
  printer->Outdent();
  printer->Outdent();
  printer->Outdent();
  printer->Outdent();
  printer->Print("\n\n");
  const EnumValueDescriptor* min_value = descriptor_->value(0);
  const EnumValueDescriptor* max_value = descriptor_->value(0);

  for (int i = 0; i < descriptor_->value_count(); i++) {
    vars["name"] = descriptor_->value(i)->name();
    vars["number"] = SimpleItoa(descriptor_->value(i)->number());

    SourceLocation valSourceLoc;
    descriptor_->value(i)->GetSourceLocation(&valSourceLoc);

    PrintComment(printer, valSourceLoc.leading_comments);
    PrintComment(printer, valSourceLoc.trailing_comments);
    printer->Print(vars, "Enum_$shortname$_$name$: int = $number$\n");

    if (descriptor_->value(i)->number() < min_value->number()) {
      min_value = descriptor_->value(i);
    }
    if (descriptor_->value(i)->number() > max_value->number()) {
      max_value = descriptor_->value(i);
    }
  }
  vars["min"] = std::to_string(min_value->number());
  vars["max"] = std::to_string(max_value->number());
  printer->Print(vars, "Enum_$shortname$_MinValue: int = $min$\n");
  printer->Print(vars, "Enum_$shortname$_MaxValue: int = $max$\n");
}

}  // namespace google::protobuf::compiler::hs
