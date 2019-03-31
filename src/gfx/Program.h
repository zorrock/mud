//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/span.h>
#include <stl/table.h>
#include <stl/vector.h>
#include <type/Unique.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

namespace mud
{
	using cstring = const char*;
	
	export_ enum class refl_ ShaderType : unsigned int
	{
		Compute,
		Fragment,
		Geometry,
		Vertex,
		Count
	};

	export_ enum class refl_ PassType : unsigned int
	{
		VoxelGI,
		Lightmap,
		Shadowmap,
		Probes,
		Clear,
		Depth,
		Normals,
		Shadow,
		Geometry,
		Lights,
		Opaque,
		Background,
		Particles,
		Alpha,
		Solid,
		Effects,
		PostProcess,
		Flip,

		Count
	};

	export_ struct refl_ MUD_GFX_EXPORT ShaderDefine
	{
		attr_ string m_name;
		attr_ string m_value;
	};

	export_ struct refl_ MUD_GFX_EXPORT ShaderBlock
	{
		attr_ uint32_t m_index;
		attr_ vector<string> m_options;
		attr_ vector<string> m_modes;
		vector<ShaderDefine> m_defines;

		meth_ void add_option(const string& name) { m_options.push_back(name); }
		meth_ void add_mode(const string& name) { m_modes.push_back(name); }
		meth_ void add_define(const string& name, const string& value) { m_defines.push_back({ name, value }); }
	};

	export_ struct refl_ MUD_GFX_EXPORT ProgramBlock
	{
		// maps a block shader option to the program option shift
		attr_ bool m_enabled = false;
		attr_ uint8_t m_option_shift = 0;
		attr_ uint8_t m_mode_shift = 0;
	};

	export_ enum class refl_ MaterialBlock : unsigned int
	{
		Base,
		Alpha,
		Solid,
		Point,
		Line,
		Lit,
		Pbr,
		Phong,
		Fresnel,
		User,
		Count
	};

	export_ class refl_ MUD_GFX_EXPORT Program
	{
	public:
		struct Version
		{
			Version() {}
			uint64_t m_version = 0;
			uint32_t m_update = 0;
			bgfx::ProgramHandle m_program = BGFX_INVALID_HANDLE;
		};

	public:
		Program(const string& name, bool compute = false);
		~Program();

		attr_ string m_name;

		meth_ void set_block(MaterialBlock block, bool enabled = true);
		meth_ void set_pass(PassType type, bool enabled = true);
		meth_ void set_source(ShaderType type, const string& source);

		string defines(const ProgramVersion& version) const;

		void reload() { m_update++; }

		void compile(GfxSystem& gfx, Version& version, bool compute = false);

		void update(GfxSystem& gfx);

		bgfx::ProgramHandle default_version();
		bgfx::ProgramHandle version(const ProgramVersion& config);

		ProgramVersion shader_version(Version& version);

		meth_ void register_blocks(const Program& program);

		meth_ void register_block(const ShaderBlock& block);

		void register_blocks(span<GfxBlock*> blocks);
		void register_options(uint8_t block, span<string> options);
		void register_modes(uint8_t block, span<string> modes);

		// maps a block index to its shader options span
		ProgramBlock m_shader_blocks[32] = {};
		uint8_t m_next_option = 0;
		vector<GfxBlock*> m_registered_blocks;

		table<ShaderType, string> m_sources = {};
		table<PassType, bool> m_passes = {};
		table<MaterialBlock, bool> m_blocks = {};

		vector<string> m_option_names;
		vector<string> m_mode_names;

		vector<ShaderDefine> m_defines;

		bool m_compute = false;
		uint32_t m_update = 1;

		uint32_t m_primitives = 0;

		struct Impl;
		unique<Impl> m_impl;

		static GfxSystem* ms_gfx_system;
	};
}
