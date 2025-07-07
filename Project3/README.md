# CPU

实现了二级流水线的CPU。（IF+EX）

CPU总架构图：

![](/cpu.png)

Control图：

<img src="./Control.png" style="zoom:33%;" />

Regfile图：

<img src="./regfile.png" style="zoom:33%;" />

其余部分实现较为零碎，见 `cpu` 文件夹中的所有 `.circ` 文件。如需打开请使用

```bash
java -jar logisim-evolution.jar
```

之后打开文件。
