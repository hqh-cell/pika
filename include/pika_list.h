// Copyright (c) 2015-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef PIKA_LIST_H_
#define PIKA_LIST_H_

#include "include/pika_command.h"
#include "include/pika_slot.h"
#include "storage/storage.h"

/*
 * list
 */
class LIndexCmd : public Cmd {
 public:
  LIndexCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LIndexCmd(*this); }

 private:
  std::string key_;
  int64_t index_ = 0;
  void DoInitial() override;
  void Clear() override { index_ = 0; }
};

class LInsertCmd : public Cmd {
 public:
  LInsertCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag), dir_(storage::After){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LInsertCmd(*this); }

 private:
  std::string key_;
  storage::BeforeOrAfter dir_;
  std::string pivot_;
  std::string value_;
  void DoInitial() override;
};

class LLenCmd : public Cmd {
 public:
  LLenCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LLenCmd(*this); }

 private:
  std::string key_;
  void DoInitial() override;
};

class LPopCmd : public Cmd {
 public:
  LPopCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LPopCmd(*this); }

 private:
  std::string key_;
  void DoInitial() override;
};

class LPushCmd : public Cmd {
 public:
  LPushCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LPushCmd(*this); }

 private:
  std::string key_;
  std::vector<std::string> values_;
  void DoInitial() override;
  void Clear() override { values_.clear(); }
};

class LPushxCmd : public Cmd {
 public:
  LPushxCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LPushxCmd(*this); }

 private:
  std::string key_;
  std::vector<std::string> values_;
  void DoInitial() override;
};

class LRangeCmd : public Cmd {
 public:
  LRangeCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LRangeCmd(*this); }

 private:
  std::string key_;
  int64_t left_ = 0;
  int64_t right_ = 0;
  void DoInitial() override;
};

class LRemCmd : public Cmd {
 public:
  LRemCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LRemCmd(*this); }

 private:
  std::string key_;
  int64_t count_ = 0;
  std::string value_;
  void DoInitial() override;
};

class LSetCmd : public Cmd {
 public:
  LSetCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LSetCmd(*this); }

 private:
  std::string key_;
  int64_t index_ = 0;
  std::string value_;
  void DoInitial() override;
};

class LTrimCmd : public Cmd {
 public:
  LTrimCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new LTrimCmd(*this); }

 private:
  std::string key_;
  int64_t start_ = 0;
  int64_t stop_ = 0;
  void DoInitial() override;
};

class RPopCmd : public Cmd {
 public:
  RPopCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new RPopCmd(*this); }

 private:
  std::string key_;
  void DoInitial() override;
};

class RPopLPushCmd : public Cmd {
 public:
  RPopLPushCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag) {
    rpop_cmd_ = std::make_shared<RPopCmd>(kCmdNameRPop, 2, kCmdFlagsWrite | kCmdFlagsSingleSlot | kCmdFlagsList);
    lpush_cmd_ = std::make_shared<LPushCmd>(kCmdNameLPush, -3, kCmdFlagsWrite | kCmdFlagsSingleSlot | kCmdFlagsList);
  };
  RPopLPushCmd(const RPopLPushCmd& other)
      : Cmd(other.name_, other.arity_, other.flag_),
        source_(other.source_),
        receiver_(other.receiver_),
        value_poped_from_source_(other.value_poped_from_source_),
        is_write_binlog_(other.is_write_binlog_) {
    rpop_cmd_ = std::make_shared<RPopCmd>(kCmdNameRPop, 2, kCmdFlagsWrite | kCmdFlagsSingleSlot | kCmdFlagsList);
    lpush_cmd_ = std::make_shared<LPushCmd>(kCmdNameLPush, -3, kCmdFlagsWrite | kCmdFlagsSingleSlot | kCmdFlagsList);
  }
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(source_);
    res.push_back(receiver_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new RPopLPushCmd(*this); }
  void DoBinlog(const std::shared_ptr<SyncMasterSlot>& slot) override;

 private:
  std::string source_;
  std::string receiver_;
  std::string value_poped_from_source_;
  bool is_write_binlog_ = false;
  //used for write binlog
  std::shared_ptr<Cmd> rpop_cmd_;
  std::shared_ptr<Cmd> lpush_cmd_;
  void DoInitial() override;
};

class RPushCmd : public Cmd {
 public:
  RPushCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new RPushCmd(*this); }

 private:
  std::string key_;
  std::vector<std::string> values_;
  void DoInitial() override;
  void Clear() override { values_.clear(); }
};

class RPushxCmd : public Cmd {
 public:
  RPushxCmd(const std::string& name, int arity, uint16_t flag) : Cmd(name, arity, flag){};
  std::vector<std::string> current_key() const override {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  void Do(std::shared_ptr<Slot> slot = nullptr) override;
  void Split(std::shared_ptr<Slot> slot, const HintKeys& hint_keys) override{};
  void Merge() override{};
  Cmd* Clone() override { return new RPushxCmd(*this); }

 private:
  std::string key_;
  std::vector<std::string> values_;
  virtual void DoInitial() override;
};
#endif
