/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** OpenGL entry points.
*/

// don't put #pragma once wrappers in this file, it gets #included
//  several times with different #defines for GL_PROC.

// base GL functionality...
GL_PROC(base_opengl,glEnable,WINGDIAPI,void,(GLenum cap))
GL_PROC(base_opengl,glDisable,WINGDIAPI,void,(GLenum cap))
GL_PROC(base_opengl,glGetIntegerv,WINGDIAPI,void,(GLenum pname, GLint *params))
GL_PROC(base_opengl,glGetString,WINGDIAPI,const GLubyte *,(GLenum name))
GL_PROC(base_opengl,glGetError,WINGDIAPI,GLenum,(void))
GL_PROC(base_opengl,glDepthMask,WINGDIAPI,void,(GLboolean flag))
GL_PROC(base_opengl,glDepthRange,WINGDIAPI,void,(GLclampd zNear, GLclampd zFar))
GL_PROC(base_opengl,glBlendFunc,WINGDIAPI,void,(GLenum sfactor, GLenum dfactor))
GL_PROC(base_opengl,glAlphaFunc,WINGDIAPI,void,(GLenum func, GLclampf ref))
GL_PROC(base_opengl,glDepthFunc,WINGDIAPI,void,(GLenum func))
GL_PROC(base_opengl,glMatrixMode,WINGDIAPI,void,(GLenum mode))
GL_PROC(base_opengl,glLoadIdentity,WINGDIAPI,void,(void))
GL_PROC(base_opengl,glScalef,WINGDIAPI,void,(GLfloat x, GLfloat y, GLfloat z))
GL_PROC(base_opengl,glViewport,WINGDIAPI,void,(GLint x, GLint y, GLsizei width, GLsizei height))
GL_PROC(base_opengl,glTranslatef,WINGDIAPI,void,(GLfloat x, GLfloat y, GLfloat z))
GL_PROC(base_opengl,glRotatef,WINGDIAPI,void,(GLfloat angle, GLfloat x, GLfloat y, GLfloat z))
GL_PROC(base_opengl,glOrtho,WINGDIAPI,void,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar))
GL_PROC(base_opengl,glScissor,WINGDIAPI,void,(GLint x, GLint y, GLsizei width, GLsizei height))
GL_PROC(base_opengl,glClearColor,WINGDIAPI,void,(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))
GL_PROC(base_opengl,glClear,WINGDIAPI,void,(GLbitfield mask))
GL_PROC(base_opengl,glPixelStorei,WINGDIAPI,void,(GLenum pname, GLint param))
GL_PROC(base_opengl,glBindTexture,WINGDIAPI,void,(GLenum target, GLuint texture))
GL_PROC(base_opengl,glTexEnvi,WINGDIAPI,void,(GLenum target, GLenum pname, GLint param))
GL_PROC(base_opengl,glTexParameterf,WINGDIAPI,void,(GLenum target, GLenum pname, GLfloat param))
GL_PROC(base_opengl,glTexParameteri,WINGDIAPI,void,(GLenum target, GLenum pname, GLint param))
GL_PROC(base_opengl,glTexImage2D,WINGDIAPI,void,(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels))
GL_PROC(base_opengl,glTexSubImage2D,WINGDIAPI,void,(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels))
GL_PROC(base_opengl,glGenTextures,WINGDIAPI,void,(GLsizei n, GLuint *textures))
GL_PROC(base_opengl,glDeleteTextures,WINGDIAPI,void,(GLsizei n, const GLuint *textures))
GL_PROC(base_opengl,glVertexPointer,WINGDIAPI,void,(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer))
GL_PROC(base_opengl,glColorPointer,WINGDIAPI,void,(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer))
GL_PROC(base_opengl,glTexCoordPointer,WINGDIAPI,void,(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer))
GL_PROC(base_opengl,glDrawArrays,WINGDIAPI,void,(GLenum mode, GLint first, GLsizei count))
GL_PROC(base_opengl,glDrawElements,WINGDIAPI,void,(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices))
GL_PROC(base_opengl,glEnableClientState,WINGDIAPI,void,(GLenum array))
GL_PROC(base_opengl,glFinish,WINGDIAPI,void,(void))
GL_PROC(base_opengl,glReadPixels,WINGDIAPI,void,(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels))

// GL_EXT_framebuffer_object ...
GL_PROC(GL_EXT_framebuffer_object,glBindRenderbufferEXT,,void,(GLenum target, GLuint name))
GL_PROC(GL_EXT_framebuffer_object,glDeleteRenderbuffersEXT,,void,(GLsizei, const GLuint *))
GL_PROC(GL_EXT_framebuffer_object,glGenRenderbuffersEXT,,void,(GLsizei, GLuint *))
GL_PROC(GL_EXT_framebuffer_object,glRenderbufferStorageEXT,,void,(GLenum, GLenum, GLsizei, GLsizei))
GL_PROC(GL_EXT_framebuffer_object,glBindFramebufferEXT,,void,(GLenum, GLuint))
GL_PROC(GL_EXT_framebuffer_object,glDeleteFramebuffersEXT,,void,(GLsizei, const GLuint *))
GL_PROC(GL_EXT_framebuffer_object,glGenFramebuffersEXT,,void,(GLsizei, GLuint *))
GL_PROC(GL_EXT_framebuffer_object,glCheckFramebufferStatusEXT,,GLenum,(GLenum))
GL_PROC(GL_EXT_framebuffer_object,glFramebufferRenderbufferEXT,,void,(GLenum, GLenum, GLenum, GLuint))
GL_PROC(GL_EXT_framebuffer_object,glFramebufferTexture2DEXT,,void,(GLenum, GLenum, GLenum, GLuint, GLint))

// GL_ARB_vertex_buffer_object ...
GL_PROC(GL_ARB_vertex_buffer_object,glBindBufferARB,,void,(GLenum, GLuint))
GL_PROC(GL_ARB_vertex_buffer_object,glDeleteBuffersARB,,void,(GLsizei, const GLuint *))
GL_PROC(GL_ARB_vertex_buffer_object,glGenBuffersARB,,void,(GLsizei, GLuint *))
GL_PROC(GL_ARB_vertex_buffer_object,glBufferDataARB,,void,(GLenum, GLsizeiptr, const GLvoid *, GLenum))
GL_PROC(GL_ARB_vertex_buffer_object,glMapBufferARB,,GLvoid*,(GLenum, GLenum))
GL_PROC(GL_ARB_vertex_buffer_object,glUnmapBufferARB,,GLboolean,(GLenum))

// end of hge_glfuncs.h ...

