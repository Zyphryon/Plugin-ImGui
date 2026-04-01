# ImGui Plugin for Zyphryon Engine

This plugin integrates [Dear ImGui](https://github.com/ocornut/imgui) with [Zyphryon](https://github.com/Zyphryon/Engine).  

---

## Features

- Full Dear ImGui integration (UI context, styling, docking, navigation).
- Plug-and-play: minimal boilerplate required to start using ImGui in your project.

---

## Usage

```cpp
#include <Plugin/ImGuiSystem.hpp>

Plugin::ImGuiSystem mImGui;

// During initialization
mImGui.Initialize(Host, Device);

// In your frame loop
mImGui.Begin(Time);

// Use ImGui normally
ImGui::Begin("Demo");
ImGui::Text("Hello from Zyphryon + ImGui!");
ImGui::End();

// Render UI
mImGui.End();
```

## 📄 License

This plugin is licensed under the MIT License – see the LICENSE file for details.

## 🤝 Contributing

We welcome contributions! Please feel free to submit Pull Requests, open Issues, or discuss new features in Discussions.