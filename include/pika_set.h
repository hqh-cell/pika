 // Copyright (c) 2015-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef PIKA_SET_H_
#define PIKA_SET_H_

#include "include/pika_command.h"
#include "include/pika_slot.h"

 /*
 * set
 */
class SAddCmd : public Cmd {
 public:
  SAddCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SAddCmd(*this); }

 private:
  std::string key_;
  std::vector<std::string> members_;
  void DoInitial() override;
};

class SPopCmd : public Cmd {
 public:
  SPopCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SPopCmd(*this); }

 private:
  std::string key_;
  int64_t count_;
  void DoInitial() override;
};

class SCardCmd : public Cmd {
 public:
  SCardCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SCardCmd(*this); }

 private:
  std::string key_;
  void DoInitial() override;
};

class SMembersCmd : public Cmd {
 public:
  SMembersCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SMembersCmd(*this); }

 private:
  std::string key_;
  void DoInitial() override;
};

class SScanCmd : public Cmd {
 public:
  SScanCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag), pattern_("*") {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SScanCmd(*this); }

 private:
  std::string key_, pattern_ = "*";
  int64_t cursor_ = 0;
  int64_t count_ = 10;
  void DoInitial() override;
  void Clear() override {
    pattern_ = "*";
    count_ = 10;
  }
};

class SRemCmd : public Cmd {
 public:
  SRemCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SRemCmd(*this); }

 private:
  std::string key_;
  std::vector<std::string> members_;
  void DoInitial() override;
};

class SUnionCmd : public Cmd {
 public:
  SUnionCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SUnionCmd(*this); }

 private:
  std::vector<std::string> keys_;
  void DoInitial() override;
};

class SUnionstoreCmd : public Cmd {
 public:
  SUnionstoreCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SUnionstoreCmd(*this); }

 private:
  std::string dest_key_;
  std::vector<std::string> keys_;
  void DoInitial() override;
};

class SInterCmd : public Cmd {
 public:
  SInterCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SInterCmd(*this); }

 private:
  std::vector<std::string> keys_;
  void DoInitial() override;
};

class SInterstoreCmd : public Cmd {
 public:
  SInterstoreCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SInterstoreCmd(*this); }

 private:
  std::string dest_key_;
  std::vector<std::string> keys_;
  void DoInitial() override;
};

class SIsmemberCmd : public Cmd {
 public:
  SIsmemberCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SIsmemberCmd(*this); }

 private:
  std::string key_, member_;
  void DoInitial() override;
};

class SDiffCmd : public Cmd {
 public:
  SDiffCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SDiffCmd(*this); }

 private:
  std::vector<std::string> keys_;
  void DoInitial() override;
};

class SDiffstoreCmd : public Cmd {
 public:
  SDiffstoreCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SDiffstoreCmd(*this); }

 private:
  std::string dest_key_;
  std::vector<std::string> keys_;
  void DoInitial() override;
};

class SMoveCmd : public Cmd {
 public:
  SMoveCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SMoveCmd(*this); }

 private:
  std::string src_key_, dest_key_, member_;
  void DoInitial() override;
};

class SRandmemberCmd : public Cmd {
 public:
  SRandmemberCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {}
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override {};
  void Merge() override {};
  Cmd* Clone() override { return new SRandmemberCmd(*this); }

 private:
  std::string key_;
  int64_t count_ = 1;
  bool reply_arr = false;
  void DoInitial() override;
  void Clear() override {
    count_ = 1;
    reply_arr = false;
  }
};

#endif
