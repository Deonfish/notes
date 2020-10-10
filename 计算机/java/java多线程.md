## 基础知识

#### 进程与线程

**为什么需要线程？**

1. 每个进程单独占用一块内存空间，若想共享这块内存空间则比较复杂。而用线程则天生共享内存空间，共享资源比较容易。
2. 线程用来实现一个进程的多个子任务并发，来提高并发程度和响应速度。如一个Servlet创建多个线程来接收多个请求，而用相同的代码处理请求。
3. 线程的切换相对于进程开销更小，所以线程的效率更高，并发程度更高，无效时间更少。

**进程和线程的区别？**

1. 进程单独占有⼀定的内存地址空间，所以进程间存在内存隔离，数据共享复杂但是同步简单。而线程共享所属进程的内存空间和资源，数据共享简单但同步复杂。（进程是分配资源的基本单位，线程是调度的基本单位）。
2. 进程单独占有⼀定的内存地址空间，进程的创建和销毁不仅需要保存寄存器和栈信息，还需要资源的分配回收以及⻚调度，开销较⼤；线程只需要保存寄存器和栈信息，开销较⼩。
3. 进程一般由系统管理，而线程一般由用户管理。



线程创建方法 ( 继承Thread 或 实现Runnable )

```java
    static class T1 extends Thread {
        @Override
        public void run() {
            System.out.println("thread1 running...");
        }
    }
    static class T2 implements Runnable {
        @Override
        public void run() {
            System.out.println("thread2 running...");
        }
    }
    public static void main(String[] args) {
        Thread t1 = new T1();
        Thread t2 = new Thread(new T2());
        Thread t3 = new Thread(() -> {
            System.out.println("thread3 running...");
        });
        t1.start();
        t2.start();
        t3.start();
    }
```

Callable实现类配合线程池

```java
 		public static class Task implements Callable<Integer> {
        @Override
        public Integer call() throws Exception {
            Thread.sleep(1000);
            return 2;
        }
    }
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        ExecutorService executorService = Executors.newCachedThreadPool();
        Task task = new Task();
        Future<Integer> result = executorService.submit(task);
        System.out.println(result.get());
    }
```

使用FutureTask类

```java
    public static class Task implements Callable<Integer> {
        @Override
        public Integer call() throws Exception {
            Thread.sleep(1000);
            return 2;
        }
    }
    public static void main(String[] args) throws ExecutionException, InterruptedException {
        ExecutorService executorService = Executors.newCachedThreadPool();
        Task task = new Task();
//        Future<Integer> result = executorService.submit(task);
//        System.out.println(result.get());
        FutureTask<Integer> futureTask = new FutureTask<>(task);
        executorService.submit(futureTask);
        System.out.println(futureTask.get());

    }
```

## 一些工具

