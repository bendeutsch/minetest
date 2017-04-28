/*
Minetest
Copyright (C) 2010-2013 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef CLOUDS_HEADER
#define CLOUDS_HEADER

#include "irrlichttypes_extrabloated.h"
#include <iostream>
#include "constants.h"
#include "cloudparameters.h"

// Menu clouds
class Clouds;
extern Clouds *g_menuclouds;

// Scene manager used for menu clouds
namespace irr{namespace scene{class ISceneManager;}}
extern irr::scene::ISceneManager *g_menucloudsmgr;

class Clouds : public scene::ISceneNode
{
public:
	Clouds(
			scene::ISceneNode* parent,
			scene::ISceneManager* mgr,
			s32 id,
			u32 seed,
			s16 cloudheight=0
	);

	~Clouds();

	/*
		ISceneNode methods
	*/

	virtual void OnRegisterSceneNode();

	virtual void render();
	
	virtual const aabb3f &getBoundingBox() const
	{
		return m_box;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return m_material;
	}
	
	/*
		Other stuff
	*/

	void step(float dtime);

	void update(v2f camera_p, video::SColorf color);
	
	void updateCameraOffset(v3s16 camera_offset)
	{
		m_camera_offset = camera_offset;
		updateBox();
	}

	void readSettings();

	void setDensity(float density)
	{
		m_density = density;
		// currently does not need bounding
	}

	void setColorBright(const video::SColor &color_bright)
	{
		m_color_bright = color_bright;
	}

	void setColorAmbient(const video::SColor &color_ambient)
	{
		m_color_ambient = color_ambient;
	}

	void setHeight(float height)
	{
		m_cloud_y = BS * height; // add bounding when necessary
		updateBox();
	}

	void setSpeed(v2f speed) { m_speed = speed; }

	void setThickness(float thickness)
	{
		m_thickness = BS * thickness;
		updateBox();
	}

private:
	void updateBox()
	{
		m_box = aabb3f(-BS * 1000000.0f, m_cloud_y - BS * m_camera_offset.Y, -BS * 1000000.0f,
				BS * 1000000.0f, m_cloud_y + m_thickness - BS * m_camera_offset.Y, BS * 1000000.0f);
	}

	video::SMaterial m_material;
	aabb3f m_box;
	s16 m_passed_cloud_y;
	float m_cloud_y;
	u16 m_cloud_radius_i;
	bool m_enable_3d;
	u32 m_seed;
	v2f m_camera_pos;
	v2f m_origin;
	v2f m_speed;
	v3s16 m_camera_offset;
	float m_density;
	float m_thickness;
	video::SColorf m_color;
	video::SColorf m_color_bright;
	video::SColorf m_color_ambient;

};



#endif
