#include "hsm.h"
#include <chrono>


class Watch : public Hsm {
public:
  Watch();

  void some_time_passed();
  void press_mode();
  void press_set();

  [[nodiscard]] auto get_time() const -> std::chrono::time_point<std::chrono::system_clock> { return current_time; }
  auto view() -> std::string { return current_view; }

private:
  Event TICK{}, MODE{}, SET{}, CHILD{};

  void tick();

  void timekeepingStd(StdEvents event);
  void settingStd(StdEvents event);

  std::chrono::time_point<std::chrono::system_clock> current_time{std::chrono::system_clock::now()};
  std::chrono::time_point<std::chrono::system_clock> temp_time{std::chrono::system_clock::now()};
  std::string current_view{};
};
