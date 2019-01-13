
// Bindings utilities
function WrapperObject() {
}
// Distribution
function Distribution() { throw "cannot construct a Distribution, no constructor in IDL" }
Distribution.prototype = Object.create(WrapperObject.prototype);
Distribution.prototype.constructor = Distribution;
Distribution.prototype.__class__ = Distribution;
Distribution.__cache__ = {};
Module['Distribution'] = Distribution;
Distribution.prototype["__destroy__"] = Distribution.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Distribution___destroy__(self);
};
// Face3
function Face3() {
    var self = this.ptr;
    this.ptr = _mud_Face3_Face3_0(self); getCache(Face3)[this.ptr] = this;
};
Face3.prototype = Object.create(WrapperObject.prototype);
Face3.prototype.constructor = Face3;
Face3.prototype.__class__ = Face3;
Face3.__cache__ = {};
Module['Face3'] = Face3;
Face3.prototype["__destroy__"] = Face3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Face3___destroy__(self);
};
// MeshPacker
function MeshPacker() {
    var self = this.ptr;
    this.ptr = _mud_MeshPacker_MeshPacker_0(self); getCache(MeshPacker)[this.ptr] = this;
};
MeshPacker.prototype = Object.create(WrapperObject.prototype);
MeshPacker.prototype.constructor = MeshPacker;
MeshPacker.prototype.__class__ = MeshPacker;
MeshPacker.__cache__ = {};
Module['MeshPacker'] = MeshPacker;
MeshPacker.prototype["__destroy__"] = MeshPacker.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_MeshPacker___destroy__(self);
};
// Plane
function Plane() {
    var self = this.ptr;
    this.ptr = _mud_Plane_Plane_0(self); getCache(Plane)[this.ptr] = this;
};
Plane.prototype = Object.create(WrapperObject.prototype);
Plane.prototype.constructor = Plane;
Plane.prototype.__class__ = Plane;
Plane.__cache__ = {};
Module['Plane'] = Plane;
Object.defineProperty(Plane.prototype, "normal", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane_get_normal(self), mud::vec3);
    },
    set: function(normal) {
        var self = this.ptr;
        /* normal <vec3> [] */
        normal = normal.ptr;
        _mud_Plane_set_normal(self, normal);
    }
});
Object.defineProperty(Plane.prototype, "distance", {
    get: function() {
        var self = this.ptr;
        return _mud_Plane_get_distance(self);
    },
    set: function(distance) {
        var self = this.ptr;
        /* distance <float> [] */
        _mud_Plane_set_distance(self, distance);
    }
});
Plane.prototype["__destroy__"] = Plane.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Plane___destroy__(self);
};
// Plane3
function Plane3() {
    var self = this.ptr;
    this.ptr = _mud_Plane3_Plane3_0(self); getCache(Plane3)[this.ptr] = this;
};
Plane3.prototype = Object.create(WrapperObject.prototype);
Plane3.prototype.constructor = Plane3;
Plane3.prototype.__class__ = Plane3;
Plane3.__cache__ = {};
Module['Plane3'] = Plane3;
Object.defineProperty(Plane3.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3_get_origin(self), mud::vec3);
    },
    set: function(origin) {
        var self = this.ptr;
        /* origin <vec3> [] */
        origin = origin.ptr;
        _mud_Plane3_set_origin(self, origin);
    }
});
Object.defineProperty(Plane3.prototype, "a", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3_get_a(self), mud::vec3);
    },
    set: function(a) {
        var self = this.ptr;
        /* a <vec3> [] */
        a = a.ptr;
        _mud_Plane3_set_a(self, a);
    }
});
Object.defineProperty(Plane3.prototype, "b", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3_get_b(self), mud::vec3);
    },
    set: function(b) {
        var self = this.ptr;
        /* b <vec3> [] */
        b = b.ptr;
        _mud_Plane3_set_b(self, b);
    }
});
Plane3.prototype["__destroy__"] = Plane3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Plane3___destroy__(self);
};
// Ray
function Ray() {
    var self = this.ptr;
    this.ptr = _mud_Ray_Ray_0(self); getCache(Ray)[this.ptr] = this;
};
Ray.prototype = Object.create(WrapperObject.prototype);
Ray.prototype.constructor = Ray;
Ray.prototype.__class__ = Ray;
Ray.__cache__ = {};
Module['Ray'] = Ray;
Object.defineProperty(Ray.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray_get_start(self), mud::vec3);
    },
    set: function(start) {
        var self = this.ptr;
        /* start <vec3> [] */
        start = start.ptr;
        _mud_Ray_set_start(self, start);
    }
});
Object.defineProperty(Ray.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray_get_end(self), mud::vec3);
    },
    set: function(end) {
        var self = this.ptr;
        /* end <vec3> [] */
        end = end.ptr;
        _mud_Ray_set_end(self, end);
    }
});
Object.defineProperty(Ray.prototype, "dir", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray_get_dir(self), mud::vec3);
    },
    set: function(dir) {
        var self = this.ptr;
        /* dir <vec3> [] */
        dir = dir.ptr;
        _mud_Ray_set_dir(self, dir);
    }
});
Object.defineProperty(Ray.prototype, "inv_dir", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray_get_inv_dir(self), mud::vec3);
    },
    set: function(inv_dir) {
        var self = this.ptr;
        /* inv_dir <vec3> [] */
        inv_dir = inv_dir.ptr;
        _mud_Ray_set_inv_dir(self, inv_dir);
    }
});
Ray.prototype["__destroy__"] = Ray.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ray___destroy__(self);
};
// Segment
function Segment() {
    var self = this.ptr;
    this.ptr = _mud_Segment_Segment_0(self); getCache(Segment)[this.ptr] = this;
};
Segment.prototype = Object.create(WrapperObject.prototype);
Segment.prototype.constructor = Segment;
Segment.prototype.__class__ = Segment;
Segment.__cache__ = {};
Module['Segment'] = Segment;
Object.defineProperty(Segment.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Segment_get_start(self), mud::vec3);
    },
    set: function(start) {
        var self = this.ptr;
        /* start <vec3> [] */
        start = start.ptr;
        _mud_Segment_set_start(self, start);
    }
});
Object.defineProperty(Segment.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Segment_get_end(self), mud::vec3);
    },
    set: function(end) {
        var self = this.ptr;
        /* end <vec3> [] */
        end = end.ptr;
        _mud_Segment_set_end(self, end);
    }
});
Segment.prototype["__destroy__"] = Segment.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Segment___destroy__(self);
};
// Shape
function Shape() { throw "cannot construct a Shape, no constructor in IDL" }
Shape.prototype = Object.create(WrapperObject.prototype);
Shape.prototype.constructor = Shape;
Shape.prototype.__class__ = Shape;
Shape.__cache__ = {};
Module['Shape'] = Shape;
Object.defineProperty(Shape.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shape_get_type(self), mud::Type);
    }});
Shape.prototype["__destroy__"] = Shape.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shape___destroy__(self);
};
// ShapeVar
function ShapeVar(shape) {
    var self = this.ptr;
    /* shape <Shape> [] */
    shape = shape.ptr;
    if (shape === undefined) { this.ptr = _mud_ShapeVar_ShapeVar_0(self); getCache(ShapeVar)[this.ptr] = this; return; }
    this.ptr = _mud_ShapeVar_ShapeVar_1(self, shape); getCache(ShapeVar)[this.ptr] = this;
};
ShapeVar.prototype = Object.create(WrapperObject.prototype);
ShapeVar.prototype.constructor = ShapeVar;
ShapeVar.prototype.__class__ = ShapeVar;
ShapeVar.__cache__ = {};
Module['ShapeVar'] = ShapeVar;
Object.defineProperty(ShapeVar.prototype, "shape", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ShapeVar_get_shape(self), mud::Shape);
    }});
ShapeVar.prototype["__destroy__"] = ShapeVar.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ShapeVar___destroy__(self);
};
// Symbol
function Symbol(fill, outline, overlay, double_sided, detail) {
    var self = this.ptr;
    /* fill <Colour> [] */
    fill = fill.ptr;
    /* outline <Colour> [] */
    if(typeof outline !== "undefined" && outline !== null) {{ outline = outline.ptr }};
    /* overlay <bool> [] */
    /* double_sided <bool> [] */
    /* detail <SymbolDetail> [] */
    if (detail && typeof detail === "object") detail = detail.ptr;
    if (fill === undefined) { this.ptr = _mud_Symbol_Symbol_0(self); getCache(Symbol)[this.ptr] = this; return; }
    if (outline === undefined) { this.ptr = _mud_Symbol_Symbol_1(self, fill); getCache(Symbol)[this.ptr] = this; return; }
    if (overlay === undefined) { this.ptr = _mud_Symbol_Symbol_2(self, fill, outline); getCache(Symbol)[this.ptr] = this; return; }
    if (double_sided === undefined) { this.ptr = _mud_Symbol_Symbol_3(self, fill, outline, overlay); getCache(Symbol)[this.ptr] = this; return; }
    if (detail === undefined) { this.ptr = _mud_Symbol_Symbol_4(self, fill, outline, overlay, double_sided); getCache(Symbol)[this.ptr] = this; return; }
    this.ptr = _mud_Symbol_Symbol_5(self, fill, outline, overlay, double_sided, detail); getCache(Symbol)[this.ptr] = this;
};
Symbol.prototype = Object.create(WrapperObject.prototype);
Symbol.prototype.constructor = Symbol;
Symbol.prototype.__class__ = Symbol;
Symbol.__cache__ = {};
Module['Symbol'] = Symbol;
Object.defineProperty(Symbol.prototype, "outline", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol_get_outline(self), mud::Colour);
    },
    set: function(outline) {
        var self = this.ptr;
        /* outline <Colour> [] */
        outline = outline.ptr;
        _mud_Symbol_set_outline(self, outline);
    }
});
Object.defineProperty(Symbol.prototype, "fill", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol_get_fill(self), mud::Colour);
    },
    set: function(fill) {
        var self = this.ptr;
        /* fill <Colour> [] */
        fill = fill.ptr;
        _mud_Symbol_set_fill(self, fill);
    }
});
Object.defineProperty(Symbol.prototype, "overlay", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Symbol_get_overlay(self));
    },
    set: function(overlay) {
        var self = this.ptr;
        /* overlay <bool> [] */
        _mud_Symbol_set_overlay(self, overlay);
    }
});
Object.defineProperty(Symbol.prototype, "double_sided", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Symbol_get_double_sided(self));
    },
    set: function(double_sided) {
        var self = this.ptr;
        /* double_sided <bool> [] */
        _mud_Symbol_set_double_sided(self, double_sided);
    }
});
Object.defineProperty(Symbol.prototype, "detail", {
    get: function() {
        var self = this.ptr;
        return _mud_Symbol_get_detail(self);
    },
    set: function(detail) {
        var self = this.ptr;
        /* detail <SymbolDetail> [] */
        if (detail && typeof detail === "object") detail = detail.ptr;
        _mud_Symbol_set_detail(self, detail);
    }
});
Object.defineProperty(Symbol.prototype, "image", {
    get: function() {
        var self = this.ptr;
        return _mud_Symbol_get_image(self);
    },
    set: function(image) {
        var self = this.ptr;
        /* image <const char*> [] */
        _mud_Symbol_set_image(self, image);
    }
});
Object.defineProperty(Symbol.prototype, "image256", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol_get_image256(self), mud::Image256);
    },
    set: function(image256) {
        var self = this.ptr;
        /* image256 <Image256> [] */
        image256 = image256.ptr;
        _mud_Symbol_set_image256(self, image256);
    }
});
Object.defineProperty(Symbol.prototype, "program", {
    get: function() {
        var self = this.ptr;
        return _mud_Symbol_get_program(self);
    },
    set: function(program) {
        var self = this.ptr;
        /* program <const char*> [] */
        _mud_Symbol_set_program(self, program);
    }
});
Symbol.prototype["__destroy__"] = Symbol.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Symbol___destroy__(self);
};
// Arc
function Arc(radius, start, end) {
    var self = this.ptr;
    /* radius <float> [] */
    /* start <float> [] */
    /* end <float> [] */
    if (radius === undefined) { this.ptr = _mud_Arc_Arc_0(self); getCache(Arc)[this.ptr] = this; return; }
    this.ptr = _mud_Arc_Arc_3(self, radius, start, end); getCache(Arc)[this.ptr] = this;
};
Arc.prototype = Object.create(WrapperObject.prototype);
Arc.prototype.constructor = Arc;
Arc.prototype.__class__ = Arc;
Arc.__cache__ = {};
Module['Arc'] = Arc;
Object.defineProperty(Arc.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Arc_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Arc_set_radius(self, radius);
    }
});
Object.defineProperty(Arc.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return _mud_Arc_get_start(self);
    },
    set: function(start) {
        var self = this.ptr;
        /* start <float> [] */
        _mud_Arc_set_start(self, start);
    }
});
Object.defineProperty(Arc.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return _mud_Arc_get_end(self);
    },
    set: function(end) {
        var self = this.ptr;
        /* end <float> [] */
        _mud_Arc_set_end(self, end);
    }
});
Arc.prototype["__destroy__"] = Arc.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Arc___destroy__(self);
};
// ArcLine
function ArcLine(center, start, middle, end) {
    var self = this.ptr;
    /* center <vec3> [] */
    center = center.ptr;
    /* start <vec3> [] */
    start = start.ptr;
    /* middle <vec3> [] */
    middle = middle.ptr;
    /* end <vec3> [] */
    end = end.ptr;
    if (center === undefined) { this.ptr = _mud_ArcLine_ArcLine_0(self); getCache(ArcLine)[this.ptr] = this; return; }
    if (end === undefined) { this.ptr = _mud_ArcLine_ArcLine_3(self, center, start, middle); getCache(ArcLine)[this.ptr] = this; return; }
    this.ptr = _mud_ArcLine_ArcLine_4(self, center, start, middle, end); getCache(ArcLine)[this.ptr] = this;
};
ArcLine.prototype = Object.create(WrapperObject.prototype);
ArcLine.prototype.constructor = ArcLine;
ArcLine.prototype.__class__ = ArcLine;
ArcLine.__cache__ = {};
Module['ArcLine'] = ArcLine;
Object.defineProperty(ArcLine.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine_get_start(self), mud::vec3);
    },
    set: function(start) {
        var self = this.ptr;
        /* start <vec3> [] */
        start = start.ptr;
        _mud_ArcLine_set_start(self, start);
    }
});
Object.defineProperty(ArcLine.prototype, "middle", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine_get_middle(self), mud::vec3);
    },
    set: function(middle) {
        var self = this.ptr;
        /* middle <vec3> [] */
        middle = middle.ptr;
        _mud_ArcLine_set_middle(self, middle);
    }
});
Object.defineProperty(ArcLine.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine_get_end(self), mud::vec3);
    },
    set: function(end) {
        var self = this.ptr;
        /* end <vec3> [] */
        end = end.ptr;
        _mud_ArcLine_set_end(self, end);
    }
});
ArcLine.prototype["__destroy__"] = ArcLine.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ArcLine___destroy__(self);
};
// Capsule
function Capsule(radius, height, axis) {
    var self = this.ptr;
    /* radius <float> [] */
    /* height <float> [] */
    /* axis <Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Capsule_Capsule_0(self); getCache(Capsule)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Capsule_Capsule_2(self, radius, height); getCache(Capsule)[this.ptr] = this; return; }
    this.ptr = _mud_Capsule_Capsule_3(self, radius, height, axis); getCache(Capsule)[this.ptr] = this;
};
Capsule.prototype = Object.create(WrapperObject.prototype);
Capsule.prototype.constructor = Capsule;
Capsule.prototype.__class__ = Capsule;
Capsule.__cache__ = {};
Module['Capsule'] = Capsule;
Object.defineProperty(Capsule.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Capsule_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Capsule_set_radius(self, radius);
    }
});
Object.defineProperty(Capsule.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Capsule_get_height(self);
    },
    set: function(height) {
        var self = this.ptr;
        /* height <float> [] */
        _mud_Capsule_set_height(self, height);
    }
});
Object.defineProperty(Capsule.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Capsule_get_axis(self);
    },
    set: function(axis) {
        var self = this.ptr;
        /* axis <Axis> [] */
        if (axis && typeof axis === "object") axis = axis.ptr;
        _mud_Capsule_set_axis(self, axis);
    }
});
Capsule.prototype["__destroy__"] = Capsule.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Capsule___destroy__(self);
};
// Cube
function Cube(center, extents) {
    var self = this.ptr;
    /* center <vec3> [] */
    center = center.ptr;
    /* extents <vec3> [] */
    extents = extents.ptr;
    if (center === undefined) { this.ptr = _mud_Cube_Cube_0(self); getCache(Cube)[this.ptr] = this; return; }
    if (extents === undefined) { this.ptr = _mud_Cube_Cube_1(self, center); getCache(Cube)[this.ptr] = this; return; }
    this.ptr = _mud_Cube_Cube_2(self, center, extents); getCache(Cube)[this.ptr] = this;
};
Cube.prototype = Object.create(WrapperObject.prototype);
Cube.prototype.constructor = Cube;
Cube.prototype.__class__ = Cube;
Cube.__cache__ = {};
Module['Cube'] = Cube;
Object.defineProperty(Cube.prototype, "extents", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Cube_get_extents(self), mud::vec3);
    },
    set: function(extents) {
        var self = this.ptr;
        /* extents <vec3> [] */
        extents = extents.ptr;
        _mud_Cube_set_extents(self, extents);
    }
});
Cube.prototype["__destroy__"] = Cube.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Cube___destroy__(self);
};
// Aabb
function Aabb(center, extents) {
    var self = this.ptr;
    /* center <vec3> [] */
    center = center.ptr;
    /* extents <vec3> [] */
    extents = extents.ptr;
    if (center === undefined) { this.ptr = _mud_Aabb_Aabb_0(self); getCache(Aabb)[this.ptr] = this; return; }
    this.ptr = _mud_Aabb_Aabb_2(self, center, extents); getCache(Aabb)[this.ptr] = this;
};
Aabb.prototype = Object.create(WrapperObject.prototype);
Aabb.prototype.constructor = Aabb;
Aabb.prototype.__class__ = Aabb;
Aabb.__cache__ = {};
Module['Aabb'] = Aabb;
Object.defineProperty(Aabb.prototype, "empty", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Aabb_get_empty(self));
    },
    set: function(empty) {
        var self = this.ptr;
        /* empty <bool> [] */
        _mud_Aabb_set_empty(self, empty);
    }
});
Aabb.prototype["__destroy__"] = Aabb.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Aabb___destroy__(self);
};
// Box
function Box() {
    var self = this.ptr;
    this.ptr = _mud_Box_Box_0(self); getCache(Box)[this.ptr] = this;
};
Box.prototype = Object.create(WrapperObject.prototype);
Box.prototype.constructor = Box;
Box.prototype.__class__ = Box;
Box.__cache__ = {};
Module['Box'] = Box;
Box.prototype["__destroy__"] = Box.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Box___destroy__(self);
};
// Circle
function Circle(radius, axis) {
    var self = this.ptr;
    /* radius <float> [] */
    /* axis <Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Circle_Circle_0(self); getCache(Circle)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Circle_Circle_1(self, radius); getCache(Circle)[this.ptr] = this; return; }
    this.ptr = _mud_Circle_Circle_2(self, radius, axis); getCache(Circle)[this.ptr] = this;
};
Circle.prototype = Object.create(WrapperObject.prototype);
Circle.prototype.constructor = Circle;
Circle.prototype.__class__ = Circle;
Circle.__cache__ = {};
Module['Circle'] = Circle;
Object.defineProperty(Circle.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Circle_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Circle_set_radius(self, radius);
    }
});
Object.defineProperty(Circle.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Circle_get_axis(self);
    },
    set: function(axis) {
        var self = this.ptr;
        /* axis <Axis> [] */
        if (axis && typeof axis === "object") axis = axis.ptr;
        _mud_Circle_set_axis(self, axis);
    }
});
Circle.prototype["__destroy__"] = Circle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Circle___destroy__(self);
};
// ConvexHull
function ConvexHull(vertices) {
    var self = this.ptr;
    /* vertices <std::vector<mud::vec3>> [] */
    vertices = vertices.ptr;
    if (vertices === undefined) { this.ptr = _mud_ConvexHull_ConvexHull_0(self); getCache(ConvexHull)[this.ptr] = this; return; }
    this.ptr = _mud_ConvexHull_ConvexHull_1(self, vertices); getCache(ConvexHull)[this.ptr] = this;
};
ConvexHull.prototype = Object.create(WrapperObject.prototype);
ConvexHull.prototype.constructor = ConvexHull;
ConvexHull.prototype.__class__ = ConvexHull;
ConvexHull.__cache__ = {};
Module['ConvexHull'] = ConvexHull;
ConvexHull.prototype["__destroy__"] = ConvexHull.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ConvexHull___destroy__(self);
};
// Cylinder
function Cylinder(radius, height, axis) {
    var self = this.ptr;
    /* radius <float> [] */
    /* height <float> [] */
    /* axis <Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Cylinder_Cylinder_0(self); getCache(Cylinder)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Cylinder_Cylinder_2(self, radius, height); getCache(Cylinder)[this.ptr] = this; return; }
    this.ptr = _mud_Cylinder_Cylinder_3(self, radius, height, axis); getCache(Cylinder)[this.ptr] = this;
};
Cylinder.prototype = Object.create(WrapperObject.prototype);
Cylinder.prototype.constructor = Cylinder;
Cylinder.prototype.__class__ = Cylinder;
Cylinder.__cache__ = {};
Module['Cylinder'] = Cylinder;
Object.defineProperty(Cylinder.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Cylinder_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Cylinder_set_radius(self, radius);
    }
});
Object.defineProperty(Cylinder.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Cylinder_get_height(self);
    },
    set: function(height) {
        var self = this.ptr;
        /* height <float> [] */
        _mud_Cylinder_set_height(self, height);
    }
});
Object.defineProperty(Cylinder.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Cylinder_get_axis(self);
    },
    set: function(axis) {
        var self = this.ptr;
        /* axis <Axis> [] */
        if (axis && typeof axis === "object") axis = axis.ptr;
        _mud_Cylinder_set_axis(self, axis);
    }
});
Cylinder.prototype["__destroy__"] = Cylinder.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Cylinder___destroy__(self);
};
// Ellipsis
function Ellipsis(radius, axis) {
    var self = this.ptr;
    /* radius <vec2> [] */
    radius = radius.ptr;
    /* axis <Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Ellipsis_Ellipsis_0(self); getCache(Ellipsis)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Ellipsis_Ellipsis_1(self, radius); getCache(Ellipsis)[this.ptr] = this; return; }
    this.ptr = _mud_Ellipsis_Ellipsis_2(self, radius, axis); getCache(Ellipsis)[this.ptr] = this;
};
Ellipsis.prototype = Object.create(WrapperObject.prototype);
Ellipsis.prototype.constructor = Ellipsis;
Ellipsis.prototype.__class__ = Ellipsis;
Ellipsis.__cache__ = {};
Module['Ellipsis'] = Ellipsis;
Object.defineProperty(Ellipsis.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ellipsis_get_radius(self), mud::vec2);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <vec2> [] */
        radius = radius.ptr;
        _mud_Ellipsis_set_radius(self, radius);
    }
});
Object.defineProperty(Ellipsis.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Ellipsis_get_axis(self);
    },
    set: function(axis) {
        var self = this.ptr;
        /* axis <Axis> [] */
        if (axis && typeof axis === "object") axis = axis.ptr;
        _mud_Ellipsis_set_axis(self, axis);
    }
});
Ellipsis.prototype["__destroy__"] = Ellipsis.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ellipsis___destroy__(self);
};
// Geometry
function Geometry() {
    var self = this.ptr;
    this.ptr = _mud_Geometry_Geometry_0(self); getCache(Geometry)[this.ptr] = this;
};
Geometry.prototype = Object.create(WrapperObject.prototype);
Geometry.prototype.constructor = Geometry;
Geometry.prototype.__class__ = Geometry;
Geometry.__cache__ = {};
Module['Geometry'] = Geometry;
Geometry.prototype["__destroy__"] = Geometry.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Geometry___destroy__(self);
};
// Grid2
function Grid2(size, space) {
    var self = this.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    /* space <vec2> [] */
    space = space.ptr;
    if (size === undefined) { this.ptr = _mud_Grid2_Grid2_0(self); getCache(Grid2)[this.ptr] = this; return; }
    if (space === undefined) { this.ptr = _mud_Grid2_Grid2_1(self, size); getCache(Grid2)[this.ptr] = this; return; }
    this.ptr = _mud_Grid2_Grid2_2(self, size, space); getCache(Grid2)[this.ptr] = this;
};
Grid2.prototype = Object.create(WrapperObject.prototype);
Grid2.prototype.constructor = Grid2;
Grid2.prototype.__class__ = Grid2;
Grid2.__cache__ = {};
Module['Grid2'] = Grid2;
Object.defineProperty(Grid2.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid2_get_size(self), mud::vec2);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <vec2> [] */
        size = size.ptr;
        _mud_Grid2_set_size(self, size);
    }
});
Object.defineProperty(Grid2.prototype, "space", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid2_get_space(self), mud::vec2);
    },
    set: function(space) {
        var self = this.ptr;
        /* space <vec2> [] */
        space = space.ptr;
        _mud_Grid2_set_space(self, space);
    }
});
Grid2.prototype["__destroy__"] = Grid2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Grid2___destroy__(self);
};
// Grid3
function Grid3(size, points) {
    var self = this.ptr;
    /* size <uvec2> [] */
    size = size.ptr;
    /* points <std::vector<mud::vec3>> [] */
    points = points.ptr;
    if (size === undefined) { this.ptr = _mud_Grid3_Grid3_0(self); getCache(Grid3)[this.ptr] = this; return; }
    if (points === undefined) { this.ptr = _mud_Grid3_Grid3_1(self, size); getCache(Grid3)[this.ptr] = this; return; }
    this.ptr = _mud_Grid3_Grid3_2(self, size, points); getCache(Grid3)[this.ptr] = this;
};
Grid3.prototype = Object.create(WrapperObject.prototype);
Grid3.prototype.constructor = Grid3;
Grid3.prototype.__class__ = Grid3;
Grid3.__cache__ = {};
Module['Grid3'] = Grid3;
Object.defineProperty(Grid3.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid3_get_size(self), mud::uvec2);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <uvec2> [] */
        size = size.ptr;
        _mud_Grid3_set_size(self, size);
    }
});
Grid3.prototype["__destroy__"] = Grid3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Grid3___destroy__(self);
};
// Line
function Line(start, end) {
    var self = this.ptr;
    /* start <vec3> [] */
    start = start.ptr;
    /* end <vec3> [] */
    end = end.ptr;
    if (start === undefined) { this.ptr = _mud_Line_Line_0(self); getCache(Line)[this.ptr] = this; return; }
    this.ptr = _mud_Line_Line_2(self, start, end); getCache(Line)[this.ptr] = this;
};
Line.prototype = Object.create(WrapperObject.prototype);
Line.prototype.constructor = Line;
Line.prototype.__class__ = Line;
Line.__cache__ = {};
Module['Line'] = Line;
Object.defineProperty(Line.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Line_get_start(self), mud::vec3);
    },
    set: function(start) {
        var self = this.ptr;
        /* start <vec3> [] */
        start = start.ptr;
        _mud_Line_set_start(self, start);
    }
});
Object.defineProperty(Line.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Line_get_end(self), mud::vec3);
    },
    set: function(end) {
        var self = this.ptr;
        /* end <vec3> [] */
        end = end.ptr;
        _mud_Line_set_end(self, end);
    }
});
Line.prototype["__destroy__"] = Line.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Line___destroy__(self);
};
// Points
function Points(points) {
    var self = this.ptr;
    /* points <std::vector<mud::vec3>> [] */
    points = points.ptr;
    if (points === undefined) { this.ptr = _mud_Points_Points_0(self); getCache(Points)[this.ptr] = this; return; }
    this.ptr = _mud_Points_Points_1(self, points); getCache(Points)[this.ptr] = this;
};
Points.prototype = Object.create(WrapperObject.prototype);
Points.prototype.constructor = Points;
Points.prototype.__class__ = Points;
Points.__cache__ = {};
Module['Points'] = Points;
Points.prototype["__destroy__"] = Points.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Points___destroy__(self);
};
// Poisson
function Poisson(size, maxRadius) {
    var self = this.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    /* maxRadius <float> [] */
    this.ptr = _mud_Poisson_Poisson_2(self, size, maxRadius); getCache(Poisson)[this.ptr] = this;
};
Poisson.prototype = Object.create(WrapperObject.prototype);
Poisson.prototype.constructor = Poisson;
Poisson.prototype.__class__ = Poisson;
Poisson.__cache__ = {};
Module['Poisson'] = Poisson;
Poisson.prototype["addPoint"] = Poisson.prototype.addPoint = function(radius, point) {
    /* radius <float> [] */
    /* point <vec3> [] */
    point = point.ptr;
    return !!(_mud_Poisson_addPoint_2(radius, point));
};
Poisson.prototype["__destroy__"] = Poisson.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Poisson___destroy__(self);
};
// Polygon
function Polygon(vertices) {
    var self = this.ptr;
    /* vertices <std::vector<mud::vec3>> [] */
    vertices = vertices.ptr;
    if (vertices === undefined) { this.ptr = _mud_Polygon_Polygon_0(self); getCache(Polygon)[this.ptr] = this; return; }
    this.ptr = _mud_Polygon_Polygon_1(self, vertices); getCache(Polygon)[this.ptr] = this;
};
Polygon.prototype = Object.create(WrapperObject.prototype);
Polygon.prototype.constructor = Polygon;
Polygon.prototype.__class__ = Polygon;
Polygon.__cache__ = {};
Module['Polygon'] = Polygon;
Polygon.prototype["__destroy__"] = Polygon.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Polygon___destroy__(self);
};
// Quad
function Quad(a, b, c, d) {
    var self = this.ptr;
    /* a <vec3> [] */
    a = a.ptr;
    /* b <vec3> [] */
    b = b.ptr;
    /* c <vec3> [] */
    c = c.ptr;
    /* d <vec3> [] */
    d = d.ptr;
    if (a === undefined) { this.ptr = _mud_Quad_Quad_0(self); getCache(Quad)[this.ptr] = this; return; }
    this.ptr = _mud_Quad_Quad_4(self, a, b, c, d); getCache(Quad)[this.ptr] = this;
};
Quad.prototype = Object.create(WrapperObject.prototype);
Quad.prototype.constructor = Quad;
Quad.prototype.__class__ = Quad;
Quad.__cache__ = {};
Module['Quad'] = Quad;
Quad.prototype["__destroy__"] = Quad.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Quad___destroy__(self);
};
// Rect
function Rect(position, size) {
    var self = this.ptr;
    /* position <vec2> [] */
    position = position.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    if (position === undefined) { this.ptr = _mud_Rect_Rect_0(self); getCache(Rect)[this.ptr] = this; return; }
    this.ptr = _mud_Rect_Rect_2(self, position, size); getCache(Rect)[this.ptr] = this;
};
Rect.prototype = Object.create(WrapperObject.prototype);
Rect.prototype.constructor = Rect;
Rect.prototype.__class__ = Rect;
Rect.__cache__ = {};
Module['Rect'] = Rect;
Object.defineProperty(Rect.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Rect_get_position(self), mud::vec2);
    },
    set: function(position) {
        var self = this.ptr;
        /* position <vec2> [] */
        position = position.ptr;
        _mud_Rect_set_position(self, position);
    }
});
Object.defineProperty(Rect.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Rect_get_size(self), mud::vec2);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <vec2> [] */
        size = size.ptr;
        _mud_Rect_set_size(self, size);
    }
});
Rect.prototype["__destroy__"] = Rect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Rect___destroy__(self);
};
// Ring
function Ring(radius, min, max) {
    var self = this.ptr;
    /* radius <float> [] */
    /* min <float> [] */
    /* max <float> [] */
    if (radius === undefined) { this.ptr = _mud_Ring_Ring_0(self); getCache(Ring)[this.ptr] = this; return; }
    this.ptr = _mud_Ring_Ring_3(self, radius, min, max); getCache(Ring)[this.ptr] = this;
};
Ring.prototype = Object.create(WrapperObject.prototype);
Ring.prototype.constructor = Ring;
Ring.prototype.__class__ = Ring;
Ring.__cache__ = {};
Module['Ring'] = Ring;
Object.defineProperty(Ring.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Ring_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Ring_set_radius(self, radius);
    }
});
Object.defineProperty(Ring.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_Ring_get_min(self);
    },
    set: function(min) {
        var self = this.ptr;
        /* min <float> [] */
        _mud_Ring_set_min(self, min);
    }
});
Object.defineProperty(Ring.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_Ring_get_max(self);
    },
    set: function(max) {
        var self = this.ptr;
        /* max <float> [] */
        _mud_Ring_set_max(self, max);
    }
});
Ring.prototype["__destroy__"] = Ring.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ring___destroy__(self);
};
// Sphere
function Sphere(radius) {
    var self = this.ptr;
    /* radius <float> [] */
    if (radius === undefined) { this.ptr = _mud_Sphere_Sphere_0(self); getCache(Sphere)[this.ptr] = this; return; }
    this.ptr = _mud_Sphere_Sphere_1(self, radius); getCache(Sphere)[this.ptr] = this;
};
Sphere.prototype = Object.create(WrapperObject.prototype);
Sphere.prototype.constructor = Sphere;
Sphere.prototype.__class__ = Sphere;
Sphere.__cache__ = {};
Module['Sphere'] = Sphere;
Object.defineProperty(Sphere.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Sphere_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Sphere_set_radius(self, radius);
    }
});
Sphere.prototype["__destroy__"] = Sphere.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Sphere___destroy__(self);
};
// SphereRing
function SphereRing(radius, min, max) {
    var self = this.ptr;
    /* radius <float> [] */
    /* min <float> [] */
    /* max <float> [] */
    if (radius === undefined) { this.ptr = _mud_SphereRing_SphereRing_0(self); getCache(SphereRing)[this.ptr] = this; return; }
    this.ptr = _mud_SphereRing_SphereRing_3(self, radius, min, max); getCache(SphereRing)[this.ptr] = this;
};
SphereRing.prototype = Object.create(WrapperObject.prototype);
SphereRing.prototype.constructor = SphereRing;
SphereRing.prototype.__class__ = SphereRing;
SphereRing.__cache__ = {};
Module['SphereRing'] = SphereRing;
Object.defineProperty(SphereRing.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_SphereRing_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_SphereRing_set_radius(self, radius);
    }
});
Object.defineProperty(SphereRing.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_SphereRing_get_min(self);
    },
    set: function(min) {
        var self = this.ptr;
        /* min <float> [] */
        _mud_SphereRing_set_min(self, min);
    }
});
Object.defineProperty(SphereRing.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_SphereRing_get_max(self);
    },
    set: function(max) {
        var self = this.ptr;
        /* max <float> [] */
        _mud_SphereRing_set_max(self, max);
    }
});
SphereRing.prototype["__destroy__"] = SphereRing.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SphereRing___destroy__(self);
};
// Spheroid
function Spheroid(radius) {
    var self = this.ptr;
    /* radius <float> [] */
    if (radius === undefined) { this.ptr = _mud_Spheroid_Spheroid_0(self); getCache(Spheroid)[this.ptr] = this; return; }
    this.ptr = _mud_Spheroid_Spheroid_1(self, radius); getCache(Spheroid)[this.ptr] = this;
};
Spheroid.prototype = Object.create(WrapperObject.prototype);
Spheroid.prototype.constructor = Spheroid;
Spheroid.prototype.__class__ = Spheroid;
Spheroid.__cache__ = {};
Module['Spheroid'] = Spheroid;
Object.defineProperty(Spheroid.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Spheroid_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Spheroid_set_radius(self, radius);
    }
});
Spheroid.prototype["__destroy__"] = Spheroid.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Spheroid___destroy__(self);
};
// Torus
function Torus(radius, solid_radius, axis) {
    var self = this.ptr;
    /* radius <float> [] */
    /* solid_radius <float> [] */
    /* axis <Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Torus_Torus_0(self); getCache(Torus)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Torus_Torus_2(self, radius, solid_radius); getCache(Torus)[this.ptr] = this; return; }
    this.ptr = _mud_Torus_Torus_3(self, radius, solid_radius, axis); getCache(Torus)[this.ptr] = this;
};
Torus.prototype = Object.create(WrapperObject.prototype);
Torus.prototype.constructor = Torus;
Torus.prototype.__class__ = Torus;
Torus.__cache__ = {};
Module['Torus'] = Torus;
Object.defineProperty(Torus.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Torus_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Torus_set_radius(self, radius);
    }
});
Object.defineProperty(Torus.prototype, "solid_radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Torus_get_solid_radius(self);
    },
    set: function(solid_radius) {
        var self = this.ptr;
        /* solid_radius <float> [] */
        _mud_Torus_set_solid_radius(self, solid_radius);
    }
});
Object.defineProperty(Torus.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Torus_get_axis(self);
    },
    set: function(axis) {
        var self = this.ptr;
        /* axis <Axis> [] */
        if (axis && typeof axis === "object") axis = axis.ptr;
        _mud_Torus_set_axis(self, axis);
    }
});
Torus.prototype["__destroy__"] = Torus.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Torus___destroy__(self);
};
// Triangle
function Triangle(size) {
    var self = this.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    if (size === undefined) { this.ptr = _mud_Triangle_Triangle_0(self); getCache(Triangle)[this.ptr] = this; return; }
    this.ptr = _mud_Triangle_Triangle_1(self, size); getCache(Triangle)[this.ptr] = this;
};
Triangle.prototype = Object.create(WrapperObject.prototype);
Triangle.prototype.constructor = Triangle;
Triangle.prototype.__class__ = Triangle;
Triangle.__cache__ = {};
Module['Triangle'] = Triangle;
Object.defineProperty(Triangle.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Triangle_get_size(self), mud::vec2);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <vec2> [] */
        size = size.ptr;
        _mud_Triangle_set_size(self, size);
    }
});
Triangle.prototype["__destroy__"] = Triangle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Triangle___destroy__(self);
};

(function() {
    function setupEnums() {
        // DrawMode
        Module['OUTLINE'] = _mud_DrawMode_OUTLINE();
        Module['PLAIN'] = _mud_DrawMode_PLAIN();
        // PrimitiveType
        Module['PrimitiveType']['Points'] = _mud_PrimitiveType_Points();
        Module['PrimitiveType']['Lines'] = _mud_PrimitiveType_Lines();
        Module['PrimitiveType']['LineLoop'] = _mud_PrimitiveType_LineLoop();
        Module['PrimitiveType']['LineStrip'] = _mud_PrimitiveType_LineStrip();
        Module['PrimitiveType']['Triangles'] = _mud_PrimitiveType_Triangles();
        Module['PrimitiveType']['TriangleStrip'] = _mud_PrimitiveType_TriangleStrip();
        Module['PrimitiveType']['TriangleFan'] = _mud_PrimitiveType_TriangleFan();
        // SymbolDetail
        Module['SymbolDetail']['Lowest'] = _mud_SymbolDetail_Lowest();
        Module['SymbolDetail']['Low'] = _mud_SymbolDetail_Low();
        Module['SymbolDetail']['Medium'] = _mud_SymbolDetail_Medium();
        Module['SymbolDetail']['High'] = _mud_SymbolDetail_High();
        Module['SymbolDetail']['Highest'] = _mud_SymbolDetail_Highest();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
