/* author: Tim */

#ifndef ENGINE_SETTINGS_H
#define ENGINE_SETTINGS_H

// This header file contins defined constants used in other parts of the engine. Changes here will propigate throughout.
#define ENTITY_MAX 1024
#define RENDER_COMPONENT_MAX 1024
#define RENDER_COMPONENT_RESERVE RENDER_COMPONENT_MAX/4	// the initial size of the vector holding RenderComponents

#define USE_RESOURCE_FILE 0

#endif