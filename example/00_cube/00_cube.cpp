#define HEADER_ONLY 0

#if !HEADER_ONLY
//#include <mud/frame.h>
#include <frame/Api.h>
#else
#ifdef _MSC_VER
#include <Windows.h>
#undef near
#undef far
#undef min
#undef max
#undef small
#undef NEAR
#undef FAR
#endif

#include <mud/infra.cpp>
#include <mud/pool.cpp>
#include <mud/jobs.cpp>
#include <mud/type.cpp>
#include <mud/ecs.cpp>
#include <mud/math.cpp>
#include <mud/geom.cpp>
#include <mud/bgfx.cpp>
#include <mud/gfx.cpp>
#include <mud/ctx.cpp>
#include <mud/ui.cpp>
#include <mud/gfx.ui.cpp>
#include <mud/ctx.glfw.cpp>
#include <mud/ui.vg.cpp>
#include <mud/frame.cpp>
#endif

#include <00_cube/00_cube.h>

using namespace mud;

void speed_key(Widget& widget, vec3& speed, Key key, vec3 speed_offset)
{
	if(widget.key_event(key, EventType::Pressed))
		speed += speed_offset;
	if(widget.key_event(key, EventType::Released))
		speed -= speed_offset;
}

void velocity_controller(Widget& widget, vec3& speed, float velocity)
{
	struct KeyMove { Key key; vec3 dir; };
	const KeyMove moves[8] =
	{
		{ Key::Up,   -Z3 }, { Key::W, -Z3 },
		{ Key::Down,  Z3 }, { Key::S,  Z3 },
		{ Key::Left, -X3 }, { Key::A, -X3 },
		{ Key::Right, X3 }, { Key::D,  X3 }
	};

	for(const KeyMove& key_move : moves)
		speed_key(widget, speed, key_move.key, key_move.dir * velocity);
}

void ex_00_cube(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);
	viewer.take_focus();

	static vec3 position = vec3(0.f);
	static vec3 speed = vec3(0.f);

	velocity_controller(viewer, speed, 0.01f);
	position += speed;

	Gnode& scene = viewer.m_scene.begin();
    Gnode& node = gfx::node(scene, {}, position);
	gfx::shape(node, Cube(), Symbol::wire(Colour::Red));
}

#ifdef _00_CUBE_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_00_cube(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
