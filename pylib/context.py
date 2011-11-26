import gfxprim_core_c as core
import gfxprim_loaders_c as loaders

def extend(cls, name=None):
  def decf(method):
    funname = name
    if not funname:
      funname = method.__name__
    type.__setattr__(cls, funname, method)
    return method
  return decf

def add_swig_getmethod(cls, name=None):
  def decf(method):
    propname = name
    if not propname:
      propname = method.__name__
    cls.__swig_getmethods__[propname] = method
  return decf

def add_swig_setmethod(cls, name=None):
  def decf(method):
    propname = name
    if not propname:
      propname = method.__name__
    cls.__swig_setmethods__[propname] = method
  return decf


def extend_context_class(_context_class = core.Context):
  """
  Extends _context_class class with convenience methods.
  Called on module inicialization.
  """

  type.__setattr__(_context_class, "__doc_2__",
    """Proxy of C GP_Context struct

    You can pass this class to wrapped GP_DrawSomething(...) as GP_Context.
    All attributes of GP_Context are accessible directly as "_attribute"
    (self._w etc.), but it is reccomended to use redefined properties:

     self.w: Context width (transformed)
     self.h: Context width (transformed)

    Some context methods are provided as class members for convenience.

    GP_Context memory allocation is handled completely by gfxprim.
    You shoud NEVER even think about self.this - this pointer will point to
    free memory after self.__del__ is called (in case of owned GP_Context).
    """)

  extend(_context_class, name='parent')(None)

  @extend(_context_class, name='__str__')
  @extend(_context_class, name='__repr__')
  def context_str(self):
    return "<Context %dx%d, %dbpp, GP_Context %sowned, %s parent>" % (
      self.w, self.h, self._bpp,
      "" if self.thisown else "not ",
      "with" if self.parent else "no")

  @add_swig_getmethod(_context_class)
  def w(self):
    return core.GP_ContextW(self)

  @add_swig_getmethod(_context_class)
  def h(self):
    return core.GP_ContextH(self)

  @extend(_context_class)
  def subcontext(self, x, y, w, h):
    "Create a subcontext (rectangular view)."
    c = core.GP_ContextSubContext(self, None, x, y, w, h)
    c.thisown = True # GP_Context IS owned (but not the pixel data)
    c.parent = self
    return c

  @extend(_context_class)
  def save(self, filename, format=None):
    """Save the image in given format (or guess it from the extension)

    Currently, JPG, PNG and P[BGP]M are supported, but not for all 
    context pixel types.
    """
    if not format:
      format = filename.rsplit('.', 1)[-1]
    format = format.lower()
    if format == 'jpg':
      res = loaders.GP_SaveJPG(filename, self, None)
    elif format == 'png':
      res = loaders.GP_SavePNG(filename, self, None)
    elif format == 'pbm':
      res = loaders.GP_SavePBM(filename, self, None)
    elif format == 'pgm':
      res = loaders.GP_SavePGM(filename, self, None)
    elif format == 'ppm':
      res = loaders.GP_SavePPM(filename, self, None)
    else:
      raise Exception("Format %r not supported.", format)
    if res != 0:
      raise Exception("Error saving %r (code %d)", filename, res)

  @extend(_context_class, name='create')
  @staticmethod
  def create(w, h, pixeltype):
    "Allocate a new w*h bitmap of given type."

    pixeltype_no = pixeltype if isinstance(pixeltype, int) else 0 # !!!
    # TODO: actually accept a PixelType
    c = core.GP_ContextAlloc(w, h, pixeltype_no)
    c.thisown = True
    return c

  @extend(_context_class, name='load')
  @staticmethod
  def load(filename):
    "Load image from given file, guess type."
    c = loaders.GP_LoadImage_SWIG(filename)
    c.thisown = True
    return c



extend_context_class()
