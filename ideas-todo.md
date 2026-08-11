# Ideas:

## General Purposed GPU dispatch pipeline system (another job system woohoo)
* During engine testing I've decided that compute shaders are just essentially extra threads for dispatching, you just need to adhere to VRAM architecture. With this in mind I think I can make a public system, called `IGPUDispatchSystem`, in which you would create and dispatch compute shaders, then sync the shader's state. Though compute dispatch is pretty low level, you'd need the `IRenderDevice` to provide functionality, so I figure that `IGPUDispatchSystem` would have its own small local abstraction of `IRenderDevice` providing very intuitive buffer, shader, and sync management. This way you can share the system with your application and actually use it along side of CPU parallized tasks, first thing I think of using this for, is resource loading.
It'd look like:
1. Loading resource file on the CPU
2. Reading the file's contents onto a buffer on CPU.
3. Giving this buffer (hopefully multiple) to the GPU.
4. Each work group looks through their given buffer contents, and creates the resource already GPU ready.
5. Write loaded resources to buffer for the CPU.
Of course you can do this on just the CPU with jobs, but where's the gimmick in that?!

## To-dos
* Implement a job system for parallization on the CPU.