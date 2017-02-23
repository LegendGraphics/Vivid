set(3rdParty_DIR	${CMAKE_CURRENT_LIST_DIR}/../3rdparty)

set(GLEW_DIR		            ${3rdParty_DIR}/glew)
set(GLEW_INCLUDE_DIR		    ${GLEW_DIR}/include)
set(GLEW_LIBRARY_DIR		    ${GLEW_DIR}/lib)
set(GLEW_LIBRARY		    optimized ${GLEW_LIBRARY_DIR}/glew32.lib 
                            debug ${GLEW_LIBRARY_DIR}/glew32.lib)      
                            
set(GLFW_DIR		            ${3rdParty_DIR}/glfw)
set(GLFW_INCLUDE_DIR		    ${GLFW_DIR}/include)
set(GLFW_LIBRARY_DIR		    ${GLFW_DIR}/lib)
set(GLFW_LIBRARY		    optimized ${GLFW_LIBRARY_DIR}/glfw3.lib 
                            debug ${GLFW_LIBRARY_DIR}/glfw3.lib)         

#set(SOIL_DIR		            ${3rdParty_DIR}/SOIL)
#set(SOIL_INCLUDE_DIR		    ${SOIL_DIR}/include)
#set(SOIL_LIBRARY_DIR		    ${SOIL_DIR}/lib)
#set(SOIL_LIBRARY		    optimized ${SOIL_LIBRARY_DIR}/SOIL.lib 
#                            debug ${SOIL_LIBRARY_DIR}/SOIL.lib)  

#set(TOLUAPP_DIR		            ${3rdParty_DIR}/toluapp)
#set(TOLUAPP_INCLUDE_DIR		    ${TOLUAPP_DIR}/include)
#set(TOLUAPP_LIBRARY_DIR		    ${TOLUAPP_DIR}/lib)
#set(TOLUAPP_LIBRARY		    optimized ${TOLUAPP_LIBRARY_DIR}/toluapp.lib 
#                            debug ${TOLUAPP_LIBRARY_DIR}/toluapp.lib)                             