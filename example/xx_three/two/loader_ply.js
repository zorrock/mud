// loader_ply.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);

var scene = viewer.scene;

if(init) {
    this.importerPLY = new two.ImporterPLY(app.gfx);
    
    var camera = viewer.camera;
    camera.fov = 35.0; camera.near = 1.0; camera.far = 15.0;
    camera.eye = new two.vec3(3.0, 0.15, 3.0);
    camera.target = new two.vec3(0.0, -0.1, 0.0);

    var pbr = app.gfx.programs.fetch('pbr/pbr');

    var bg = two.rgb(0x72645b);
    bg = new two.Colour(bg.r, bg.g, bg.b);
    
    viewer.viewport.clear_colour = bg;
    scene.env.background.colour = bg;
    scene.env.radiance.colour = bg;
    scene.env.radiance.energy = 1.0;
    //scene.fog = new THREE.Fog( 0x72645b, 2, 15 );
    
    var zeroq = new two.quat(new two.vec3(0.0));

    function add_light(scene, d, color, intensity, shadows) {

        var dir = two.look_dir(new two.vec3(0.0, -0.5, -0.5));
        var n = scene.nodes().add(new two.Node3(new two.vec3(0.0), two.look_dir(d)));
        //var l = scene.lights().add(new two.Light(n, two.LightType.Direct, shadows, two.rgb(0xffaa00), intensity));
        var l = scene.lights().add(new two.Light(n, two.LightType.Direct, shadows, color, intensity));
        //l.shadow_range = 4.0;

        //l.shadow_flags = two.CSM_Stabilize;
        //l.shadow_bias = 0.1;
        //l.shadow_num_splits = 2;
        //directionalLight.shadow.bias = -0.001;
    }

    // Ground

    {
        var material = app.gfx.materials.create('ground'); var m = material;
            m.program = pbr;
            m.pbr.albedo.value = two.rgb(0x999999);
            m.pbr.roughness.value = 0.0;
            //m.pbr.specular = two.rgb(0x101010);
            // Phong

        var model = app.gfx.shape(new two.Rect(new two.vec2(0.0), new two.vec2(40.0)));
        var n = scene.nodes().add(new two.Node3(new two.vec3(0.0, -0.5, 0.0), zeroq));
        scene.items().add(new two.Item(n, model, 0, material));
    }

    var material = app.gfx.materials.create('ply'); var m = material;
        m.program = pbr;
        m.base.flat_shaded = true;
        m.pbr.albedo.value = two.rgb(0x0055ff);
        m.pbr.roughness.value = 0.0;

    // PLY file

    var dolphin = app.gfx.models.file('dolphins'); // .ply
    
    var ndolphin = scene.nodes().add(new two.Node3(new two.vec3(-0.2, 0.0, 0.3), new two.quat(new two.vec3(-Math.PI / 2, 0.0, 0.0)), new two.vec3(0.001)));
    scene.items().add(new two.Item(ndolphin, dolphin, 0, material));

    var lucy = app.gfx.models.file('Lucy100k'); // .ply

    var nlucy = scene.nodes().add(new two.Node3(new two.vec3(-0.2, 0.02, -0.2), zeroq, new two.vec3(0.0006)));
    scene.items().add(new two.Item(nlucy, lucy, 0, material));

    // Lights

    //scene.add( new THREE.HemisphereLight( 0x443333, 0x111122 ) );

    //add_light(scene, new two.vec3(-1.0, -1.0, -1.0), two.rgb(0xffffff), 1.35, true);
    add_light(scene, new two.vec3(-0.5, -1.0, 1.0), two.rgb(0xffaa00), 1.0, false);
}

var timer = app.gfx.time * 0.5;

var camera = viewer.camera;
camera.eye.x = Math.sin(timer) * 2.5;
camera.eye.z = Math.cos(timer) * 2.5;