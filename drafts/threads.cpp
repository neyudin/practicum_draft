#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>

int main()
{
	std::vector<std::future<int>> fs;
	int a, b;

	std::mutex m;
	std::vector<std::packaged_task<int()>> tasks;

	std::condition_variable cv;

	std::thread t([&]() {
		std::packaged_task<int()> task;
		while (1) {
			{
				std::unique_lock<std::mutex> lock(m);
				cv.wait(lock, [&] () { return tasks.size() > 0; });

				task = std::move(tasks.back());
				tasks.pop_back();
			}
			task();
		}
	});

	t.detach();
	std::thread([&]() {
		int i = 0;
		while (1) {
			while (i < fs.size()) {
				std::cout << fs[i].get() << std::endl;
				++i;
			}
		}
	}).detach();

	while(std::cin >> a >> b) {
		std::cout << std::this_thread::get_id() << std::endl;
		auto task = std::packaged_task<int()>([=]() {
			std::cout << std::this_thread::get_id() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return a + b;
		});
		fs.emplace_back(task.get_future());
		{
			std::lock_guard<std::mutex> lock(m);
			tasks.emplace_back(std::move(task));
			cv.notify_all();
		}
	}
	return 0;
}
