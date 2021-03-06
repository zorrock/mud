//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <stl/algorithm.h>
#include <infra/Vector.h>
#include <infra/StringOps.h>
#include <infra/File.h>
#include <math/Vec.hpp>
#include <ctx/Context.h>
#include <ui/UiWindow.h>
#include <ui/Api.h>
#endif

#include <cstdio>

namespace mud
{
	map<string, Style*> UiWindow::s_styles;

	UiWindow::UiWindow(Context& context, Vg& vg, User* user)
		: m_resource_path(context.m_resource_path)
		, m_context(context)
		, m_vg(vg)
		, m_renderer(vg)
		, m_atlas(uvec2(1024U))
		, m_size(context.m_size)
		, m_user(user)
	{
		this->init();
		this->resize(context.m_size, context.m_fb_size);
	}

	UiWindow::~UiWindow()
	{
		for(auto& image : m_images)
			if(image->d_handle != -1)
			{
				m_vg.unload_image(*image);
			}
	}

	void UiWindow::init()
	{
		this->init_styles();

		printf("INFO: Initializing UiWindow: resource path %s\n", m_resource_path.c_str());
		m_vg.setup_context();

		this->init_resources();
		this->load_resources();

		styles().setup(*this);

		m_root_sheet = oconstruct<Ui>(*this);

		m_context.init_input(m_root_sheet->m_mouse, m_root_sheet->m_keyboard);
	}

	void UiWindow::init_styles()
	{
		styles();

		ui::cursor_styles();
		ui::scrollbar_styles();
		ui::dropdown_styles();
		ui::table_styles();
		ui::expandbox_styles();
		ui::treenode_styles();
		ui::tabber_styles();
		ui::menu_styles();
		ui::toolbar_styles();
		ui::window_styles();
		ui::dock_styles();
		ui::canvas_styles();
		ui::node_styles();
		ui::file_styles();
	}

	void UiWindow::reset_styles()
	{
		styles() = {};

		ui::cursor_styles() = {};
		ui::scrollbar_styles() = {};
		ui::dropdown_styles() = {};
		ui::table_styles() = {};
		ui::expandbox_styles() = {};
		ui::treenode_styles() = {};
		ui::tabber_styles() = {};
		ui::menu_styles() = {};
		ui::toolbar_styles() = {};
		ui::window_styles() = {};
		ui::dock_styles() = {};
		ui::canvas_styles() = {};
		ui::node_styles() = {};
		ui::file_styles() = {};
	}

	void UiWindow::init_resources()
	{
		string sprite_path = m_resource_path + "/interface/uisprites";

		printf("INFO: Loading Images in path %s\n", sprite_path.c_str());

		vector<Image> images;
		load_folder_images(images, sprite_path, "");

		auto visit_folder = [&](const string& folder)
		{
			load_folder_images(images, sprite_path + folder + "/", string(folder) + "/");
		};

		visit_folders(sprite_path.c_str(), visit_folder);

		m_images = convert<object<Image>>(images, [](const Image& image) { return oconstruct<Image>(image); });
	}

	void UiWindow::load_resources()
	{
		m_vg.load_default_font();

		vector<Image*> images;
		for(auto& image : m_images) images.push_back(image.get());

		vector<unsigned char> atlas = m_atlas.generate_atlas(images);
		m_vg.load_image_RGBA(m_atlas.m_image, atlas.data());
	}

	Image& UiWindow::create_image(cstring name, uvec2 size, uint8_t* data, bool filtering)
	{
		m_images.push_back(construct<Image>(name, name, size));
		Image& image = *m_images.back();
		image.d_filtering = filtering;
		m_vg.load_image_RGBA(image, data);
		return image;
	}

	void UiWindow::remove_image(Image& image)
	{
		remove_if(m_images, [&](object<Image>& current) { return current.get() == &image; });
		m_vg.unload_image(image);
	}

	Image* UiWindow::find_image(cstring name)
	{
		for(auto& image : m_images)
			if(image->d_name == name)
				return image.get();
		return nullptr;
	}

	void UiWindow::resize(const uvec2& size, const uvec2& fb_size)
	{
		printf("INFO: ui window - resize to (%i, %i) - pixel size (%i, %i)\n", int(size.x), int(size.y), int(fb_size.x), int(fb_size.y));
		m_size = size;
		m_context.reset_fb(fb_size);
		m_root_sheet->m_frame.set_size(vec2(fb_size));
	}

	bool UiWindow::input_frame()
	{
		bool pursue = !m_shutdown;
		pursue &= m_context.next_frame();

		if(m_size != m_context.m_size)
			this->resize(m_context.m_size, m_context.m_fb_size);

		m_root_sheet->input_frame();

		m_root_sheet->m_frame.relayout();

		return pursue;
	}

	void UiWindow::render_frame()
	{
		//m_root_sheet->render_frame();

		if(m_context.m_render_system.m_manual_render)
		{
			m_renderer.render(*m_root_sheet->m_frame.m_layer, m_context.m_pixel_ratio);
			// add sub layers
		}

		m_root_sheet->clear_events();
	}

	void UiWindow::shutdown()
	{
		m_shutdown = true;
	}
}
