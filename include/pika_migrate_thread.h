#ifndef PIKA_MIGRATE_THREAD_H_
#define PIKA_MIGRATE_THREAD_H_

#include "include/pika_client_conn.h"
#include "include/pika_command.h"
#include "include/pika_slot.h"
#include "net/include/net_cli.h"
#include "net/include/net_thread.h"
#include "pika_client_conn.h"
#include "storage/storage.h"
#include "strings.h"

void WriteDelKeyToBinlog(const std::string &key, const std::shared_ptr<Slot>& slot);
static int DoMigrate(net::NetCli *cli, std::string send_str);

class PikaMigrateThread;
class PikaParseSendThread : public net::Thread {
 public:
  PikaParseSendThread(PikaMigrateThread *migrate_thread, const std::shared_ptr<Slot>& slot_);
  ~PikaParseSendThread();

  bool Init(const std::string &ip, int64_t port, int64_t timeout_ms, int64_t mgrtkeys_num);
  void ExitThread(void);

 private:
  int MigrateOneKey(net::NetCli *cli, const std::string key, const char key_type, bool async);
  void DelKeysAndWriteBinlog(std::deque<std::pair<const char, std::string>> &send_keys, const std::shared_ptr<Slot>& slot);
  bool CheckMigrateRecv(int64_t need_receive_num);
  virtual void *ThreadMain();

 private:
  std::string dest_ip_;
  int64_t dest_port_ = 0;
  int64_t timeout_ms_ = 60;
  int32_t mgrtkeys_num_ = 0;
  std::atomic<bool> should_exit_;
  PikaMigrateThread *migrate_thread_ = nullptr;
  net::NetCli *cli_ = nullptr;
  pstd::Mutex working_mutex_;
  std::shared_ptr<Slot> slot_;
};

class PikaMigrateThread : public net::Thread {
 public:
  PikaMigrateThread();
  virtual ~PikaMigrateThread();
  bool ReqMigrateBatch(const std::string &ip, int64_t port, int64_t time_out, int64_t slot_num, int64_t keys_num,
                       const std::shared_ptr<Slot>& slot);
  int ReqMigrateOne(const std::string &key, const std::shared_ptr<Slot>& slot);
  void GetMigrateStatus(std::string *ip, int64_t *port, int64_t *slot, bool *migrating, int64_t *moved,
                        int64_t *remained);
  void CancelMigrate(void);
  void IncWorkingThreadNum(void);
  void DecWorkingThreadNum(void);
  void OnTaskFailed(void);
  void AddResponseNum(int32_t response_num);

 private:
  void ResetThread(void);
  void DestroyThread(bool is_self_exit);
  void NotifyRequestMigrate(void);
  bool IsMigrating(std::pair<const char, std::string> &kpair);
  void ReadSlotKeys(const std::string &slotKey, int64_t need_read_num, int64_t &real_read_num, int32_t *finish);
  bool CreateParseSendThreads(int32_t dispatch_num);
  void DestroyParseSendThreads(void);
  virtual void *ThreadMain();

 private:
  std::string dest_ip_;
  int64_t dest_port_ = 0;
  int64_t timeout_ms_ = 60;
  int64_t slot_id_ = 0;
  int64_t keys_num_ = 0;
  std::shared_ptr<Slot> slot_;
  std::atomic<bool> is_migrating_;
  std::atomic<bool> should_exit_;
  std::atomic<bool> is_task_success_;
  std::atomic<int32_t> send_num_;
  std::atomic<int32_t> response_num_;
  std::atomic<int64_t> moved_num_;
  std::shared_ptr<Slot> slot;

  bool request_migrate_ = false;
  pstd::CondVar request_migrate_cond_;
  std::mutex request_migrate_mutex_;

  int32_t workers_num_ = 0;
  std::vector<PikaParseSendThread *> workers_;

  std::atomic<int32_t> working_thread_num_;
  pstd::CondVar workers_cond_;
  std::mutex workers_mutex_;

  std::deque<std::pair<const char, std::string>> mgrtone_queue_;
  std::mutex mgrtone_queue_mutex_;

  int64_t cursor_ = 0;
  std::deque<std::pair<const char, std::string>> mgrtkeys_queue_;
  pstd::CondVar mgrtkeys_cond_;
  std::mutex mgrtkeys_queue_mutex_;

  std::map<std::pair<const char, std::string>, std::string> mgrtkeys_map_;
  std::mutex mgrtkeys_map_mutex_;

  std::mutex migrator_mutex_;

  friend class PikaParseSendThread;
};

#endif

/* EOF */