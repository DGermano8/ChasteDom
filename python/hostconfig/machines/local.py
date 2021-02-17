import os

petsc_ver = 3.9
petsc_path='/usr/local/Cellar/petsc/3.9.3/'
petsc_build_name = ''
petsc_build_name_profile = ''
petsc_build_name_optimized = ''

noccache = "true"

other_includepaths = ['/usr/local/opt/libxsd',
                      '/usr/local/include/']

other_libpaths = [ '/usr/X11/lib',
                  '/usr/local/lib/']

blas_lapack = []
other_libraries = ['X11', 'boost_serialization-mt', 'boost_filesystem-mt', 'boost_system-mt','xerces-c', 'z', 'hdf5', 'parmetis','metis']


ldflags='-framework Accelerate'


def Configure(prefs, build):
    """Set up the build configuring.
    
    prefs can specify which version of various libraries we should use, and which optional libraries.
    
    build is an instance of BuildTypes.BuildType.
    """

    # VTK setup
    global use_vtk
    use_vtk = True
    if use_vtk:
        #homebrew installs vtk5 without simlinks
        other_includepaths.append('/usr/local/Cellar/vtk/8.1.1_2/include/vtk-8.1/')
        other_libpaths.append('/usr/local/Cellar/vtk/8.1.1_2/lib/')
        other_libraries.extend(['vtkIOXML-8.1', 'vtkCommonCore-8.1', 'vtkCommonDataModel-8.1', 'vtkCommonExecutionModel-8.1','vtkFiltersCore-8.1','libvtkFiltersGeometry-8.1'])


    # CVODE setup
    global use_cvode
    use_cvode = True
    if use_cvode:
        DetermineCvodeVersion('/usr/local/include')
        other_libraries.extend(['sundials_cvode', 'sundials_nvecserial'])
