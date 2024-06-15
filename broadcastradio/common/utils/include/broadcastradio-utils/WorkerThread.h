/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ANDROID_HARDWARE_BROADCASTRADIO_COMMON_WORKERTHREAD_H
#define ANDROID_HARDWARE_BROADCASTRADIO_COMMON_WORKERTHREAD_H

#include <chrono>
#include <queue>
#include <thread>

#include <android-base/thread_annotations.h>

namespace android {

class WorkerThread {
   public:
    WorkerThread();
    virtual ~WorkerThread();

    void schedule(std::function<void()> task, std::chrono::milliseconds delay);
    void schedule(std::function<void()> task, std::function<void()> cancelTask,
                  std::chrono::milliseconds delay);
    void cancelAll();

   private:
    struct Task {
        std::chrono::time_point<std::chrono::steady_clock> when;
        std::function<void()> what;
        std::function<void()> onCanceled;
    };
    friend bool operator<(const Task& lhs, const Task& rhs);

    std::mutex mMut;
    bool mIsTerminating GUARDED_BY(mMut);
    std::condition_variable mCond GUARDED_BY(mMut);
    std::thread mThread;
    std::priority_queue<Task> mTasks GUARDED_BY(mMut);

    void threadLoop();
};

}  // namespace android

#endif  // ANDROID_HARDWARE_BROADCASTRADIO_COMMON_WORKERTHREAD_H
