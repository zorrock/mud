#pragma once

#include <frame/Forward.h>

#include <infra/Api.h>
#include <ecs/Api.h>
#include <jobs/Api.h>
#include <ui/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>

namespace mud
{
	using Selection = vector<Ref>;

	struct refl_ ShellContext
	{
		Docksystem m_docksystem;
		attr_ Widget* m_screen = nullptr;
		attr_ Dockbar* m_dockbar = nullptr;
	};
	
	using ShellUpdate = void(*)(Shell&);
	//using ShellUpdate = std::function<void(Shell&)>;

	class refl_ Shell
	{
	public:
		constr_ Shell(const string& resource_path, const string& exec_path = "");
		~Shell();

		void init();
		void run(const ShellUpdate& func, size_t iterations = 0U);

		meth_ bool begin_frame();
		meth_ bool end_frame();

		meth_ bool pump();

	public:
		attr_ string m_exec_path;
		attr_ string m_resource_path;
		
		attr_ JobSystem m_job_system;
		attr_ GfxSystem m_gfx_system;
		attr_ ShellContext m_editor;

		unique<Context> m_context = nullptr;
		unique<Vg> m_vg = nullptr;
		unique<UiWindow> m_ui_window = nullptr;

		attr_ Ui* m_ui = nullptr;

		ShellUpdate m_pump = nullptr;
	};

	void shell_context(Widget& parent, ShellContext& context);
}

