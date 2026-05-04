#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
		initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
	GLFWwindow* window;
	vk::raii::Context  context;
	vk::raii::Instance instance = nullptr;

	void createInstance() {
		vk::ApplicationInfo appInfo("Hello Triangle",
                                          VK_MAKE_VERSION( 1, 0, 0 ),
                                          "No Engine",
                                          VK_MAKE_VERSION( 1, 0, 0 ),
                                          vk::ApiVersion14
		);

		uint32_t glfwExtensionCount = 0;
		auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		// Check if the required GLFW extensions are supported by the Vulkan implementation.
		auto extensionProperties = context.enumerateInstanceExtensionProperties();
		for (uint32_t i = 0; i < glfwExtensionCount; ++i)
		{
			if (std::ranges::none_of(extensionProperties,
									[glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
									{ return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
			{
				throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
			}
		}

		vk::InstanceCreateInfo createInfo{};
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		instance = vk::raii::Instance(context, createInfo);

		// auto extensions = context.enumerateInstanceExtensionProperties();
		
		// std::cout << "available extensions:\n";

		// for (const auto& extension : extensions) {
		// 	std::cout << '\t' << extension.extensionName << '\n';
		// }
	}

	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
		createInstance();

    }

    void mainLoop() {
		while (!glfwWindowShouldClose(window)) 
		{
			glfwPollEvents();
		}

    }

    void cleanup() {
		 glfwDestroyWindow(window);

    	glfwTerminate();

    }
};

int main()
{
    try
    {
        HelloTriangleApplication app;
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}