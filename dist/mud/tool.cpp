#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/ui.h>
#include <mud/pool.h>
#include <mud/uio.h>
#include <mud/tree.h>
#include <mud/lang.h>
#include <mud/ecs.h>
#include <mud/gfx.edit.h>
#include <mud/tool.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/ctx.h>
#include <mud/gfx.ui.h>
#include <mud/infra.h>
#include <mud/type.h>



#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
}


#ifdef MUD_MODULES
module mud.tool;
#else
#include <stl/algorithm.h>
#endif

namespace mud
{
	ActionStack::ActionStack()
		: m_done()
		, m_undone()
	{}

	ActionStack::~ActionStack()
	{}

	void ActionStack::push(object<EditorAction> action)
	{
		m_undone.clear();
		//action->apply();
		m_done.push_back(move(action));
	}

	void ActionStack::redo()
	{
		if(m_undone.empty())
			return;

		m_undone.back()->apply();
		m_done.push_back(pop(m_undone));
	}

	void ActionStack::undo()
	{
		if(m_done.empty())
			return;

		m_done.back()->undo();
		m_undone.push_back(pop(m_done));
	}

	UndoTool::UndoTool(ToolContext& context)
		: Tool(context, "Undo", type<UndoTool>())
	{}

	void UndoTool::activate()
	{
		m_context.m_action_stack->undo();
		m_state = ToolState::Done;
	}

	RedoTool::RedoTool(ToolContext& context)
		: Tool(context, "Redo", type<RedoTool>())
	{}

	void RedoTool::activate()
	{
		m_context.m_action_stack->redo();
		m_state = ToolState::Done;
	}
}


#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	Brush::Brush(ToolContext& context, cstring name, Type& type)
		: SpatialTool(context, name, type)
		, m_world_snap(false)
		, m_work_plane(Y3, 0.f)
	{
		this->add_option(oconstruct<PlaneSnapOption>(*this));
		this->add_option(oconstruct<WorldSnapOption>(*this));
	}

	void Brush::process(Viewer& viewer, const vector<Ref>& selection)
	{
		UNUSED(selection);
		Widget& screen = ui::overlay(viewer);

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			m_position = this->raycast_target(viewer, mouse_event);
			m_symbol_position = m_position;
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			this->begin(m_position);
			this->update(m_position);
			this->end();
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			this->begin(m_position);
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			this->update(m_position);
			static_cast<MouseEvent*>(screen.m_events->event(DeviceType::MouseLeft, EventType::Dragged))->consume(screen); // @todo this works, and not the next one
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			this->end();
			mouse_event.consume(screen);
		}

		viewer.m_controller->process(static_cast<Viewer&>(screen)); // @HACK @UGLY it's not a viewer !!

		this->paint(viewer.m_scene->m_graph.subi(this));
	}

	vec3 Brush::raycast_target(Viewer& viewer, MouseEvent& mouse_event)
	{
		if(m_world_snap)
		{
#if 0
			Ray ray = viewer.ray(mouse_event.m_relative);
			return as<PhysicWorld>(m_origin.m_world).ground_point(ray);
#endif
			return vec3();
		}
		else
		{
			Ray ray = viewer.m_viewport.ray(mouse_event.m_relative);
			return plane_segment_intersection(m_work_plane, { ray.m_start, ray.m_end });
		}
	}

	PlaneSnapOption::PlaneSnapOption(Brush& tool)
		: ToolOption("PlaneSnap")
		, m_tool(tool)
	{}

	void PlaneSnapOption::activate()
	{
		m_tool.m_world_snap = false;
	}

	void PlaneSnapOption::deactivate()
	{
		m_tool.m_world_snap = true;
	}

	WorldSnapOption::WorldSnapOption(Brush& tool)
		: ToolOption("WorldSnap")
		, m_tool(tool)
	{}

	void WorldSnapOption::activate()
	{
		m_tool.m_world_snap = true;
	}

	void WorldSnapOption::deactivate()
	{
		m_tool.m_world_snap = false;
	}

	PlaceBrush::PlaceBrush(ToolContext& context)
		: Brush(context, "Place", type<PlaceBrush>())
		, m_creator(type<Transform>())
	{
		//m_creator.setPrototype(type<OLight>());
	}

	void PlaceBrush::activate()
	{
		m_creator.injector().m_args[0] = var(size_t(0));
		//m_creator.injector().m_args[1] = Ref(m_origin);
		m_state = ToolState::Active;
	}

	void PlaceBrush::update(const vec3& position)
	{
		UNUSED(position);
		//Entity& entity = m_creator.create<OLight>().m_spatial;
		//entity.set_position(position);
	}

	void PlaceBrush::paint(Gnode& parent)
	{
		UNUSED(parent);
	}

	CircleBrush::CircleBrush(ToolContext& context)
		: Brush(context, "Circle", type<CircleBrush>())
		, m_creator(type<Node3>())
		, m_radius(50.f)
		, m_maxSpotRadius(10.f)
		, m_accumulate(false)
	{
		//m_creator.setPrototype(type<OLight>());
	}

	void CircleBrush::paint(Gnode& parent)
	{
		UNUSED(parent);
		Gnode& self = gfx::node(parent);
		gfx::shape(self, Circle(m_radius, Axis::Y), Symbol(Colour::White, Colour::AlphaGrey));
	}

	void CircleBrush::activate()
	{
		m_creator.injector().m_args[0] = var(size_t(0));
		//m_creator.injector().m_args[1] = Ref(m_origin);
		m_state = ToolState::Active;
	}

	void CircleBrush::update(const vec3& position)
	{
		if(!m_accumulate)
			this->clearStroke(position);

		float side = m_radius * 2.f;
		m_distribution = oconstruct<Poisson>(vec2{ side }, m_maxSpotRadius);

		vec3 point;
		while(m_distribution->addPoint(m_maxSpotRadius, point))
		{
			vec3 pos(position.x + point.x - m_radius, position.y, position.z + point.y - m_radius);

			if(filter(position, pos))
			{
				//OLight& light = m_creator.create<OLight>();
				//light.m_spatial.set_position(pos);
				//m_stroke.push_back(&light);
			}
		}
	}

	void CircleBrush::clearStroke(const vec3& center)
	{
		UNUSED(center);
#if 0
		for(OLight*& entity : m_stroke)
			if(entity && this->filter(center, entity->m_spatial.m_position))
			{
				entity->m_spatial.m_parent->detach(entity->m_spatial);
				m_creator.destroy(entity);
				entity = nullptr;
			}
#endif
	}

	bool CircleBrush::filter(const vec3& center, vec3& position)
	{
		//return distance2(position, center) <= m_radius * m_radius;
		return length2(center - position) <= m_radius * m_radius;
	}

	ScriptedBrush::ScriptedBrush(ToolContext& context, Script& script)
		: Brush(context, "Scripted Brush", type<ScriptedBrush>())
		, m_call(script)
		, m_script(script)
	{}

	void ScriptedBrush::activate()
	{
		m_state = ToolState::Active;
	}

	void ScriptedBrush::update(const vec3& position)
	{
		m_call.m_args[0] = var(position);
		m_call();
	}

	void ScriptedBrush::paint(Gnode& parent)
	{
		UNUSED(parent);
	}
}


#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	EditContext::EditContext(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
		, m_undo_tool(m_tool_context)
		, m_redo_tool(m_tool_context)
		, m_work_plane() //vec3(0.f, 10.f, 0.f), Entity::FrontVector, Entity::RightVector)
		, m_translate_tool(m_tool_context)
		, m_rotate_tool(m_tool_context)
		, m_scale_tool(m_tool_context)
		, m_view_tools(m_tool_context)
		//, m_place_brush(m_tool_context)
	{
		m_tool_context.m_action_stack = &m_action_stack;
	}

	EditContext::~EditContext()
	{}

	void EditContext::set_tool(ViewportTool& tool, Viewer& viewer)
	{
		UNUSED(viewer);
		m_tool = &tool;
		m_spatial_tool = try_as<SpatialTool>(tool);
	}

	void brush_preview(Widget& parent, Brush& brush)
	{
		UNUSED(brush);
		Widget& self = ui::stack(parent);
		UNUSED(self);
	}

	void brush_options(Widget& parent, Brush& brush)
	{
		brush_preview(parent, brush);
		object_edit(parent, Ref(&brush));
	}

	void current_brush_edit(Widget& parent, EditContext& context)
	{
		Widget& self = section(parent, "Current Brush");
		if(context.m_brush)
			brush_options(self, *context.m_brush);
	}

	bool edit_tool(Widget& parent, Tool& tool, cstring icon)
	{
		Widget& self = ui::toolbutton(parent, icon);
		self.set_state(ACTIVE, tool.m_state == ToolState::Active);
		return self.activated();
	}
		
	void tools_transform(Widget& toolbar, EditContext& context)
	{
		//if(edit_tool(toolbar, "(empty)"))
		//	context.m_tool = nullptr;
		if(edit_tool(toolbar, context.m_undo_tool, "(undo)"))
			context.m_undo_tool.activate();
		if(edit_tool(toolbar, context.m_redo_tool, "(redo)"))
			context.m_redo_tool.activate();
		if(edit_tool(toolbar, context.m_translate_tool, "(translate)"))
			context.set_tool(context.m_translate_tool, *context.m_viewer);
		if(edit_tool(toolbar, context.m_rotate_tool, "(rotate)"))
			context.set_tool(context.m_rotate_tool, *context.m_viewer);
		if(edit_tool(toolbar, context.m_scale_tool, "(scale)"))
			context.set_tool(context.m_scale_tool, *context.m_viewer);

		for(auto& brush : context.m_custom_brushes)
			if(edit_tool(toolbar, *brush, brush->m_name.c_str()))
			{
				context.set_tool(*brush, *context.m_viewer);
				context.m_brush = brush.get();
			}
	}

	void edit_transform(Widget& parent, EditContext& context)
	{
		Widget& self = ui::toolbar(parent);
		tools_transform(self, context);

		if(context.m_brush)
			brush_options(parent, *context.m_brush);
	}

	void console_view(Widget& parent, LuaInterpreter& lua)
	{
		static string feed = "console v0.1";
		static string line = "type lua code here";
		static string command = "";

		ui::console(parent, feed, line, command, 18);
		if(command != "")
		{
			lua.call(command.c_str());
			feed += "\n<< " + lua.flush();
			command = "";
		}
	}

	void object_editor(Widget& parent, const vector<Ref>& selection)
	{
		Widget& self = section(parent, "Inspector");

		if(!selection.empty() && selection[0])
		{
			Ref selected = selection[0];
			Widget& sheet = ui::widget(*self.m_body, styles().sheet, (void*)selected.m_value);
			if(selected.m_type->is<EntityRef>())
				entity_edit(sheet, { as_ent(selected), 0 });
			else
				object_edit(sheet, selected);
		}
	}

	void edit_tools(Widget& screen, Docker& docker, EditContext& context)
	{
		context.m_tool_context.m_action_stack = &context.m_action_stack;
		context.m_tool_context.m_work_plane = &context.m_work_plane;

		//if(Widget* dock = ui::dockitem(dockbar, "Library", { 0 }))
		//	library_section(section, { &type<World>(), &type<Entity>() }, game.m_selection);
		if(Widget* dock = ui::dockitem(docker, "Inspect", { 2U }))
			object_editor(*dock, context.m_selection);
		if(Widget* dock = ui::dockitem(docker, "Edit", { 3U }))
			edit_transform(*dock, context);
		if(Widget* dock = ui::dockitem(docker, "Script", { 4U }))
			script_editor(*dock, context.m_script_editor);
		//if(Widget* dock = ui::dockitem(*context.m_dockbar, "VisualScript", { 5U }))
		//	visual_script_edit(self, shell.m_editor.m_script_editor);
		if(Widget* dock = ui::dockitem(docker, "Gfx", { 6U }))
			edit_gfx_system(*dock, context.m_gfx_system);
		if(Widget* dock = ui::dockitem(docker, "Ui", { 7U }))
			ui_debug(*dock, screen);

		if(context.m_spatial_tool && context.m_viewer)
			context.m_spatial_tool->process(*context.m_viewer, context.m_selection);
	}

	void edit_tools(Widget& screen, EditContext& context)
	{
		edit_tools(screen, *context.m_dockbar, context);
	}

	void edit_context(Widget& parent, EditContext& context, bool tools)
	{
		Widget& board = ui::board(parent);
		context.m_screen = &ui::board(board);
		context.m_dockbar = &ui::dockbar(board, context.m_docksystem);

		if(tools)
			edit_tools(*context.m_screen, context);
	}
}


#ifdef MUD_MODULES
module mud.tool;
#else
#include <stl/algorithm.h>
#endif

namespace mud
{
	Tool::Tool(ToolContext& context, cstring name, Type& type)
		: m_type(type)
		, m_context(context)
		, m_name(name)
		, m_state(ToolState::Inactive)
	{}

	void Tool::add_option(object<ToolOption> option)
	{
		UNUSED(option);
	}

	void Tool::commit(object<EditorAction> action)
	{
		action->apply();
		m_context.m_action_stack->push(move(action));
	}

	void Tool::activate()
	{
		m_state = ToolState::Active;
	}

	void Tool::deactivate()
	{
		m_state = ToolState::Inactive;
	}

	ViewportTool::ViewportTool(ToolContext& context, cstring name, Type& type)
		: Tool(context, name, type)
	{}

	vector<Transform*> ViewportTool::gather_transforms(const vector<Ref>& objects)
	{
		vector<Transform*> transforms;
		for(Ref object : objects)
		{
			Var transform;
			if(convert(Var(object), type<Transform>(), transform))
				transforms.push_back(&val<Transform>(transform));
		}
		return transforms;
	}

	SpatialTool::SpatialTool(ToolContext& context, cstring name, Type& type)
		: ViewportTool(context, name, type)
	{}

	Colour gizmo_colour(float hue, bool active)
	{
		return Colour::hsl(hue, active ? 0.9f : 0.6f, active ? 0.5f : 0.3f);
	}

	vec3 gizmo_grab_linear(Viewer& viewer, const Transform& space, Axis axis)
	{
		vec3 direction = space.m_rotation * to_vec3(axis);
		vec3 normal = space.m_rotation * c_tangents[uint(axis)];
		vec3 projected = plane_segment_intersection(Plane(space.m_position, space.m_position + direction, space.m_position + normal), to_segment(viewer.mouse_ray()));
		return nearest_point_on_line(space.m_position, direction, projected);
	}

	vec3 gizmo_grab_planar(Viewer& viewer, const Transform& space, Axis normal)
	{
		Plane plane(space.m_position, space.m_rotation * to_vec3(normal));
		return plane_segment_intersection(plane, to_segment(viewer.mouse_ray()));
	}

	TransformAction::TransformAction(span<Transform*> targets)
		: m_targets(to_vector(targets))
	{}

	void TransformAction::apply()
	{
		for(Transform* transform : m_targets)
			this->apply(*transform);
	}

	void TransformAction::undo()
	{
		for(Transform* transform : m_targets)
			this->undo(*transform);
	}

	TransformTool::TransformTool(ToolContext& context, cstring name, Type& type)
		: SpatialTool(context, name, type)
	{}

	TransformTool::~TransformTool()
	{}

	bool TransformTool::enabled(const vector<Ref>& selection)
	{
		for(Ref object : selection)
			if(this->test_target(object))
				return true;
		return false;
	}

	void TransformTool::paint(Gnode& parent)
	{
		Gnode& self = gfx::node(parent, {}, m_transform);

		for(auto& gizmo : m_gizmos)
		{
			gizmo->m_handle = gizmo->draw_handle(self);
			gizmo->draw_gizmo(self, &*gizmo == m_current);
		}

#ifdef MUD_DEBUG_TRANSFORM_POINTS
		Gnode& start = gfx::node(parent, {}, m_grab_start);
		gfx::shape(start, Sphere(0.1f), Symbol(Colour::Pink, Colour::None, true));

		Gnode& end = gfx::node(parent, {}, m_grab_end);
		gfx::shape(end, Sphere(0.1f), Symbol(Colour::Pink, Colour::None, true));
#endif
	}

	void TransformTool::refresh()
	{}

	void TransformTool::process(Viewer& viewer, const vector<Ref>& targets)
	{
		Widget& screen = viewer;//= ui::overlay(viewer);

		this->refresh();

		vector<Transform*> transforms = gather_transforms(targets);
		m_transform = average_transforms(transforms);

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			if(!m_dragging)
			{
				auto callback = [&](Item* item) { m_current = &this->gizmo(*item); };
				viewer.picker(1).pick_point(viewer.m_viewport, mouse_event.m_relative, callback, ItemFlag::Ui);
			}
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			m_dragging = m_current;
			m_drag_start = mouse_event.m_relative;
			m_grab_start = m_current->grab_point(viewer, mouse_event.m_relative);
			m_action = this->create_action(transforms);
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
		{
			m_grab_end = m_current->grab_point(viewer, mouse_event.m_relative);

			m_action->undo();
			m_action->update(m_grab_start, m_grab_end);
			m_action->apply();
			mouse_event.consume(screen);
		}

		if(MouseEvent mouse_event = screen.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
		{
			m_dragging = nullptr;
			m_action->undo();
			this->commit(move(m_action));
			mouse_event.consume(screen);
		}

		viewer.m_controller->process(static_cast<Viewer&>(screen)); // @HACK @UGLY it's not a viewer !!
		//viewport_picker(viewer, screen, targets);

		this->paint(viewer.m_scene->m_graph.subi(this));
	}

	Gizmo& TransformTool::gizmo(Item& item)
	{
		for(auto& gizmo : m_gizmos)
			if(gizmo->m_handle == &item)
				return *gizmo;

		return *m_gizmos.front();
	}
}
#ifndef USE_STL
#ifdef MUD_MODULES
module mud.tool;
#else
#include <stl/vector.hpp>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_TOOL_EXPORT vector<Transform*>;
	template class MUD_TOOL_EXPORT vector<unique<Gizmo>>;
	template class MUD_TOOL_EXPORT vector<unique<ToolOption>>;
	template class MUD_TOOL_EXPORT vector<unique<Brush>>;
	template class MUD_TOOL_EXPORT vector<unique<EditorAction>>;
}
#endif

#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_TOOL_EXPORT Type& type<mud::ToolState>() { static Type ty("ToolState", sizeof(mud::ToolState)); return ty; }
    
    
    template <> MUD_TOOL_EXPORT Type& type<mud::EditContext>() { static Type ty("EditContext", sizeof(mud::EditContext)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::EditorAction>() { static Type ty("EditorAction", sizeof(mud::EditorAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::Gizmo>() { static Type ty("Gizmo", sizeof(mud::Gizmo)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::Tool>() { static Type ty("Tool", sizeof(mud::Tool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ToolContext>() { static Type ty("ToolContext", sizeof(mud::ToolContext)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ToolOption>() { static Type ty("ToolOption", sizeof(mud::ToolOption)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::Brush>() { static Type ty("Brush", type<mud::SpatialTool>(), sizeof(mud::Brush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::CircleBrush>() { static Type ty("CircleBrush", type<mud::Brush>(), sizeof(mud::CircleBrush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::PlaceBrush>() { static Type ty("PlaceBrush", type<mud::Brush>(), sizeof(mud::PlaceBrush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::PlaneSnapOption>() { static Type ty("PlaneSnapOption", type<mud::ToolOption>(), sizeof(mud::PlaneSnapOption)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::RedoTool>() { static Type ty("RedoTool", type<mud::Tool>(), sizeof(mud::RedoTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::SpatialTool>() { static Type ty("SpatialTool", type<mud::ViewportTool>(), sizeof(mud::SpatialTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::CopyTool>() { static Type ty("CopyTool", type<mud::TransformTool>(), sizeof(mud::CopyTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::FrameViewTool>() { static Type ty("FrameViewTool", type<mud::ViewportTool>(), sizeof(mud::FrameViewTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::RotateTool>() { static Type ty("RotateTool", type<mud::TransformTool>(), sizeof(mud::RotateTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ScaleTool>() { static Type ty("ScaleTool", type<mud::TransformTool>(), sizeof(mud::ScaleTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ScriptedBrush>() { static Type ty("ScriptedBrush", type<mud::Brush>(), sizeof(mud::ScriptedBrush)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TransformAction>() { static Type ty("TransformAction", type<mud::EditorAction>(), sizeof(mud::TransformAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::CopyAction>() { static Type ty("CopyAction", type<mud::TranslateAction>(), sizeof(mud::CopyAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::RotateAction>() { static Type ty("RotateAction", type<mud::TransformAction>(), sizeof(mud::RotateAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ScaleAction>() { static Type ty("ScaleAction", type<mud::TransformAction>(), sizeof(mud::ScaleAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TransformGizmo>() { static Type ty("TransformGizmo", type<mud::Gizmo>(), sizeof(mud::TransformGizmo)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TranslateAction>() { static Type ty("TranslateAction", type<mud::TransformAction>(), sizeof(mud::TranslateAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TranslateTool>() { static Type ty("TranslateTool", type<mud::TransformTool>(), sizeof(mud::TranslateTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::UndoTool>() { static Type ty("UndoTool", type<mud::Tool>(), sizeof(mud::UndoTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ViewAction>() { static Type ty("ViewAction", type<mud::EditorAction>(), sizeof(mud::ViewAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ViewportTool>() { static Type ty("ViewportTool", type<mud::Tool>(), sizeof(mud::ViewportTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::TransformTool>() { static Type ty("TransformTool", type<mud::SpatialTool>(), sizeof(mud::TransformTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::ViewTool>() { static Type ty("ViewTool", type<mud::ViewportTool>(), sizeof(mud::ViewTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneAction>() { static Type ty("WorkPlaneAction", type<mud::EditorAction>(), sizeof(mud::WorkPlaneAction)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneTool>() { static Type ty("WorkPlaneTool", type<mud::Tool>(), sizeof(mud::WorkPlaneTool)); return ty; }
    template <> MUD_TOOL_EXPORT Type& type<mud::WorldSnapOption>() { static Type ty("WorldSnapOption", type<mud::ToolOption>(), sizeof(mud::WorldSnapOption)); return ty; }
}


#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	CopyAction::CopyAction(span<Transform*> targets)
		: TranslateAction(targets)
		//, m_injector(type<Transform>())
	{}

	void CopyAction::apply(Transform& transform)
	{
		//	m_copies.push_back(&as<Transform>(m_creator.cloneObject(transform)));
		TranslateAction::apply(transform);
	}

	void CopyAction::undo(Transform& transform)
	{
		// m_copies[transform].destroy();
		TranslateAction::undo(transform);
	}

 	CopyTool::CopyTool(ToolContext& context)
		: TransformTool(context, "Copy", type<CopyTool>())
		, m_action()
	{}

	void CopyTool::begin(const vec3& position)
	{
		UNUSED(position);
		//m_action = oconstruct<CopyAction>(m_targets); // @kludge brute cast
	}

	void CopyTool::update(const vec3& position)
	{
		m_action->update(position, vec3());
		//m_action->apply();
	}

	void CopyTool::end()
	{
		this->commit(move(m_action));
	}

	object<TransformAction> CopyTool::create_action(span<Transform*> targets)
	{
		return oconstruct<CopyAction>(targets);
	}
}


#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	RotateAction::RotateAction(span<Transform*> targets, const vec3& axis)
		: TransformAction(targets)
		, m_axis(axis)
		, m_angle(0.f)
	{}

	void RotateAction::apply(Transform& transform)
	{
		transform.m_rotation = transform.m_rotation * angle_axis(m_angle, m_axis);
	}

	void RotateAction::undo(Transform& transform)
	{
		transform.m_rotation = transform.m_rotation * angle_axis(-m_angle, m_axis);
	}

	void RotateAction::update(const vec3& start, const vec3& end)
	{
		// @kludge : why negative axis ?
		m_angle = oriented_angle(normalize(start), normalize(end), m_axis); 
	}

	RotateTool::RotateTool(ToolContext& context)
		: TransformTool(context, "Rotate", type<RotateTool>())
	{
		m_gizmos.push_back(rotation_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(rotation_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(rotation_gizmo(Axis::Z, 2.f / 3.f));
		m_current = &*m_gizmos.front();
	}

	Item& rotate_gizmo(Gnode& parent, Axis axis, Colour colour, float ring_radius, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, Zero3, ZeroQuat);
		return gfx::shape(node, Torus(1.f, ring_radius, axis), Symbol(colour, Colour::None, true, true), ItemFlag::Render | flags);
	}

	class RotationGizmo : public TransformGizmo
	{
	public:
		RotationGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return gizmo_grab_planar(viewer, m_tool.m_transform, m_axis) - m_tool.m_transform.m_position; };

		virtual Item* draw_handle(Gnode& parent) { return &rotate_gizmo(parent, m_axis, Colour::Invisible, 0.05f, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { rotate_gizmo(parent, m_axis, gizmo_colour(m_hue, active), 0.01f); };
	};

	unique<Gizmo> RotateTool::rotation_gizmo(Axis axis, float hue)
	{
		return make_unique<RotationGizmo>(*this, axis, hue);
	}

	object<TransformAction> RotateTool::create_action(span<Transform*> targets)
	{
		vec3 axis = m_current == &*m_gizmos[0] ? -X3
				  : m_current == &*m_gizmos[1] ?  Y3
											   : -Z3;
		return oconstruct<RotateAction>(targets, axis);
	}

}



#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	ScaleAction::ScaleAction(span<Transform*> targets)
		: TransformAction(targets)
		, m_scale_offset(Zero3)
	{}

	void ScaleAction::apply(Transform& transform)
	{
		transform.m_scale += m_scale_offset;
	}

	void ScaleAction::undo(Transform& transform)
	{
		transform.m_scale += -m_scale_offset;
	}

	void ScaleAction::update(const vec3& start, const vec3& end)
	{
		m_scale_offset = end - start;
	}

 	ScaleTool::ScaleTool(ToolContext& context)
		: TransformTool(context, "Scale", type<ScaleTool>())
	{
		m_gizmos.push_back(linear_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(linear_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(linear_gizmo(Axis::Z, 2.f / 3.f));
		m_gizmos.push_back(planar_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(planar_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(planar_gizmo(Axis::Z, 2.f / 3.f));
		m_gizmos.push_back(uniform_gizmo());
		m_current = &*m_gizmos.front();
	}

	Item& scale_1d_gizmo(Gnode& parent, Axis axis, Colour colour, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, to_vec3(axis), ZeroQuat);
		//return gfx::shape(node, Quad(0.2f, c_tangents[uint(axis)], c_binormals[uint(axis)]), Symbol(colour, Colour::None, true), flags);
		return gfx::shape(node, Cube(0.05f), Symbol(colour, Colour::None, true), flags);
	}

	Item& scale_2d_gizmo(Gnode& parent, Axis axis, Colour colour, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, 0.5f * to_vec3(axis), ZeroQuat);
		return gfx::shape(node, Quad(0.2f, c_tangents[uint(axis)], c_binormals[uint(axis)]), Symbol(colour, Colour::None, true, true), flags);
	}

	Item& scale_3d_gizmo(Gnode& parent, Colour colour, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, Zero3, ZeroQuat);
		return gfx::shape(node, Cube(0.1f), Symbol(colour, Colour::None, true), flags);
	}

	class ScaleLinearGizmo : public TransformGizmo
	{
	public:
		ScaleLinearGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return inverse(m_tool.m_transform.m_rotation) * gizmo_grab_linear(viewer, m_tool.m_transform, m_axis); };

		virtual Item* draw_handle(Gnode& parent) { return &scale_1d_gizmo(parent, m_axis, Colour::Invisible, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { scale_1d_gizmo(parent, m_axis, gizmo_colour(m_hue, active)); };
	};

	class ScalePlanarGizmo : public TransformGizmo
	{
	public:
		ScalePlanarGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return inverse(m_tool.m_transform.m_rotation) * gizmo_grab_planar(viewer, m_tool.m_transform, m_axis); };

		virtual Item* draw_handle(Gnode& parent) { return &scale_2d_gizmo(parent, m_axis, Colour::Invisible, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { scale_2d_gizmo(parent, m_axis, gizmo_colour(m_hue, active)); };
	};

	class ScaleUniformGizmo : public TransformGizmo
	{
	public:
		ScaleUniformGizmo(TransformTool& tool) : TransformGizmo(tool) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos)
		{
			vec2 delta = (pos - m_tool.m_drag_start) * 5.f / viewer.m_frame.m_size;
			return fabs(delta.x) > fabs(delta.y) ? vec3(delta.x) : vec3(delta.y);
		};

		virtual Item* draw_handle(Gnode& parent) { return &scale_3d_gizmo(parent, Colour::Invisible, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { scale_3d_gizmo(parent, active ? Colour::White : Colour::AlphaWhite); };
	};

	unique<Gizmo> ScaleTool::linear_gizmo(Axis axis, float hue)
	{
		return make_unique<ScaleLinearGizmo>(*this, axis, hue);
	}

	unique<Gizmo> ScaleTool::planar_gizmo(Axis normal, float hue)
	{
		return make_unique<ScaleLinearGizmo>(*this, normal, hue);
	}

	unique<Gizmo> ScaleTool::uniform_gizmo()
	{
		return make_unique<ScaleUniformGizmo>(*this);
	}

	object<TransformAction> ScaleTool::create_action(span<Transform*> targets)
	{
		return oconstruct<ScaleAction>(targets);
	}

}


#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	TranslateAction::TranslateAction(span<Transform*> targets)
		: TransformAction(targets)
		, m_translation(Zero3)
	{}

	void TranslateAction::apply(Transform& transform)
	{
		transform.m_position += m_translation;
	}

	void TranslateAction::undo(Transform& transform)
	{
		transform.m_position += -m_translation;
	}

	void TranslateAction::update(const vec3& start, const vec3& end)
	{
		m_translation = end - start;
	}

 	TranslateTool::TranslateTool(ToolContext& context)
		: TransformTool(context, "Translate", type<TranslateTool>())
	{
		m_gizmos.push_back(linear_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(linear_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(linear_gizmo(Axis::Z, 2.f / 3.f));
		m_gizmos.push_back(planar_gizmo(Axis::X, 0.f));
		m_gizmos.push_back(planar_gizmo(Axis::Y, 1.f / 3.f));
		m_gizmos.push_back(planar_gizmo(Axis::Z, 2.f / 3.f));
		m_current = &*m_gizmos.front();
	}

	Item& translate_1d_gizmo(Gnode& parent, Axis axis, Colour colour, float radius, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, to_vec3(axis), ZeroQuat);
		return gfx::shape(node, Cylinder(radius, 1.f, axis), Symbol(colour, Colour::None, true), flags);
	}

	Item& translate_2d_gizmo(Gnode& parent, Axis axis, Colour colour, uint32_t flags = 0U)
	{
		Gnode& node = gfx::transform(parent, {}, 0.5f * (c_tangents[uint(axis)] + c_binormals[uint(axis)]), ZeroQuat);
		return gfx::shape(node, Quad(0.3f, c_tangents[uint(axis)], c_binormals[uint(axis)]), Symbol(colour, Colour::None, true, true), flags);
	}

	class TranslateLinearGizmo : public TransformGizmo
	{
	public:
		TranslateLinearGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return gizmo_grab_linear(viewer, m_tool.m_transform, m_axis); };

		virtual Item* draw_handle(Gnode& parent) { return &translate_1d_gizmo(parent, m_axis, Colour::Invisible, 0.05f, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { translate_1d_gizmo(parent, m_axis, gizmo_colour(m_hue, active), 0.02f); };
	};

	class TranslatePlanarGizmo : public TransformGizmo
	{
	public:
		TranslatePlanarGizmo(TransformTool& tool, Axis axis, float hue) : TransformGizmo(tool, axis, hue) {}

		virtual vec3 grab_point(Viewer& viewer, const vec2& pos) { UNUSED(pos); return gizmo_grab_planar(viewer, m_tool.m_transform, m_axis); };

		virtual Item* draw_handle(Gnode& parent) { return &translate_2d_gizmo(parent, m_axis, Colour::Invisible, ItemFlag::Ui); };
		virtual void draw_gizmo(Gnode& parent, bool active) { translate_2d_gizmo(parent, m_axis, gizmo_colour(m_hue, active)); };;
	};

	unique<Gizmo> TranslateTool::linear_gizmo(Axis axis, float hue)
	{
		return make_unique<TranslateLinearGizmo>(*this, axis, hue);
	}

	unique<Gizmo> TranslateTool::planar_gizmo(Axis normal, float hue)
	{
		return make_unique<TranslatePlanarGizmo>(*this, normal, hue);
	}

	object<TransformAction> TranslateTool::create_action(span<Transform*> targets)
	{
		return oconstruct<TranslateAction>(targets);
	}

}


#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	ViewAction::ViewAction(Camera& camera, const vec3& eye, const vec3& target)
		: m_camera(camera)
		, m_eye{ camera.m_eye, eye }
		, m_target{ camera.m_target, target }
	{}

	void ViewAction::apply()
	{
		m_camera.m_eye = m_eye[End];
		m_camera.m_target = m_target[End];
	}

	void ViewAction::undo()
	{
		m_camera.m_eye = m_eye[START];
		m_camera.m_target = m_target[START];
	}

	FrameViewTool::FrameViewTool(ToolContext& context)
		: ViewportTool(context, "Frame", type<ViewTool>())
	{}

	void FrameViewTool::activate()
	{
		vec3 vision = m_context.m_camera->m_target - m_context.m_camera->m_eye;
		vector<Transform*> transforms = gather_transforms(*m_context.m_selection);
		Transform transform = average_transforms(transforms);
		this->commit(oconstruct<ViewAction>(*m_context.m_camera, transform.m_position - vision, transform.m_position));
		m_state = ToolState::Done;
	}

	ViewTool::ViewTool(ToolContext& context, cstring name, const vec3& offset)
		: ViewportTool(context, name, type<ViewTool>())
		, m_offset(offset)
	{}

	void ViewTool::activate()
	{
		vec3 target = m_context.m_camera->m_target;
		this->commit(oconstruct<ViewAction>(*m_context.m_camera, target + m_offset, target));
		m_state = ToolState::Done;
	}
}


#ifdef MUD_MODULES
module mud.tool;
#else
#endif

namespace mud
{
	WorkPlaneAction::WorkPlaneAction(Plane& workPlane, const Plane& plane)
		: m_workPlane(workPlane)
		, m_startPlane(m_workPlane)
		, m_endPlane(plane)
	{}

	void WorkPlaneAction::apply()
	{
		m_workPlane = m_endPlane;
	}

	void WorkPlaneAction::undo()
	{
		m_workPlane = m_startPlane;
	}

	WorkPlaneTool::WorkPlaneTool(ToolContext& context, cstring name, const Plane& plane)
		: Tool(context, name, type<WorkPlaneTool>())
		, m_plane(plane)
	{}

	void WorkPlaneTool::activate()
	{
		m_action = oconstruct<WorkPlaneAction>(*m_context.m_work_plane, m_plane);
		this->commit(move(m_action));
		m_state = ToolState::Done;
	}
}
