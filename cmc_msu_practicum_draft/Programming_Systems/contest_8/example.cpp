#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>

int main()
{
	std::vector<std::future<int>> fs;
	int a, b;
	//bool end = false;

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

	//t.detach();
	std::thread printer([&]() {
		unsigned i = 0;
		while (1) {
			while (i < fs.size()) {
				std::cout << fs[i].get() << std::endl;
				++i;
			}
		}
	});

	while(std::cin >> a >> b) {
		auto task = std::packaged_task<int()>([=]() {
			return a + b;
		});
		fs.emplace_back(task.get_future());
		{
			std::lock_guard<std::mutex> lock(m);
			tasks.emplace_back(std::move(task));
			cv.notify_all();
		}
	}
	//end = true;
	printer.join();
	return 0;
}