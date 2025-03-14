# Algorithm Practice

这是一个用于练习算法的项目，使用 CMake 进行构建和管理。项目支持在 Windows 和其他平台上构建，并将可执行文件输出到根目录的 `bin` 目录中。

## 项目结构

- `lru等一级子目录`: 包含各个算法的实现。
- `bin/`: 存放生成的可执行文件。
- `build/`: 存放CMake构建的临时文件

## 构建步骤

1. **在根目录下运行 CMake**：

   使用以下命令在根目录下生成构建文件：

   ```bash
   cmake -S . -B build
   ```

2. **编译项目**：

   使用以下命令在 `build` 目录中编译项目：

   ```bash
   cmake --build build
   ```

   这将会在 `bin` 目录中生成所有可执行文件。

## 运行可执行文件

编译完成后，您可以在 `bin` 目录下找到生成的可执行文件，并运行它们。例如：

```bash
./bin/lru.exe
```

## 添加新算法

1. 在项目根目录下创建一个新的子目录。
2. 在新子目录中添加源文件和一个 `CMakeLists.txt` 文件。
3. 在 `CMakeLists.txt` 中使用 `add_executable_with_dependencies` 函数来添加可执行文件。
4. CMake 会自动检测并添加新的子目录。

## 依赖

- CMake 3.10 或更高版本
- C++11 编译器

## 注意事项

- 项目配置已设置为不生成 `.pdb` 文件。
- 所有生成的可执行文件将直接放置在 `bin` 目录中，而不会在其下创建 `Debug` 或 `Release` 等子目录。
