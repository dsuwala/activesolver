from code import interact
import sys
from activeSolver import Box, System, Particle, Point2D, ParticleList, Evolver, RandomClass
import math
import numpy as np
import vtk
import matplotlib.pyplot as plt


def dump_vtp(p, outfile):
    """
    Output the system as a VTP file for direct visualisation in ParaView.
    Parameter
    ---------
      outfile : string
        Name of the output file.
    Note
    ----
      Caller should ensure that the file has correct extension
    """

    points = vtk.vtkPoints()
    ids = vtk.vtkIntArray()
    n = vtk.vtkDoubleArray()
    v = vtk.vtkDoubleArray()
    f = vtk.vtkDoubleArray()
    radius = vtk.vtkDoubleArray()

    ids.SetNumberOfComponents(1)
    n.SetNumberOfComponents(3)
    v.SetNumberOfComponents(3)
    f.SetNumberOfComponents(3)
    radius.SetNumberOfComponents(1)

    ids.SetName("id")
    n.SetName("director")
    v.SetName("velocity")
    f.SetName("force")
    radius.SetName("radius")

    for i in range(len(p)):
        points.InsertNextPoint([p[i].r.x, p[i].r.y, 0.0])
        ids.InsertNextValue(i)
        n.InsertNextTuple([p[i].n.x, p[i].n.y, 0.0])
        v.InsertNextTuple([p[i].v.x, p[i].v.y, 0.0])
        f.InsertNextTuple([p[i].f.x, p[i].f.y, 0.0])
        radius.InsertNextValue(p[i].rad)


    polyData = vtk.vtkPolyData()
    polyData.SetPoints(points)
    polyData.GetPointData().AddArray(ids)
    polyData.GetPointData().AddArray(n)
    polyData.GetPointData().AddArray(v)
    polyData.GetPointData().AddArray(f)
    polyData.GetPointData().AddArray(radius)
    writer = vtk.vtkXMLPolyDataWriter()
    writer.SetFileName(outfile)

    if vtk.VTK_MAJOR_VERSION <= 5:
        writer.SetInput(polyData)
    else:
        writer.SetInputData(polyData)
    writer.SetDataModeToAscii()
    writer.Write()

def calculateMSD(particles, particles0):
    # returns msd for a given lists of particles

    msd = 0
    
    for id in range(0, len(particles)):
        m = particles[id].r - particles0[id].r
        msd += m.norm()**2

    return  msd / len(particles)


def main():

    random = RandomClass(123123)

    phi = 0.04
    radius = 1.0

    bx = 5
    by = 5
    # N = 1000
    
    b = 100 #box size
    dt = 1e-5
    # rcutGlob = 2.25
    #rcutGlob = 2**(1./6.) * 2 * radius

    size = Point2D(b + 10, b + 10)
    box  = Box(size)
    system = System(box)

    N = math.floor((phi * size.x * size.x) / (math.pi * radius))

    points = [ Point2D(random.randreal(-b / 2.0, b / 2.0), random.randreal(-b / 2.0, b / 2.0)) for n in range(0, N) ]
    velocities = [ Point2D(random.randreal(-b / 2.0, b / 2.0), random.randreal(-b / 2.0, b / 2.0)) for n in range(0, N) ]
    angles = [random.randreal(-math.pi, math.pi) for n in range(0, N)]

    particles = [Particle(0, points[n], angles[n], velocities[n], radius) for n in range(0, len(points))]


    # points2 = [Point2D(1.0, 0.0), Point2D(3.26, 0.0) ]   #, Point2D(5.52, 0.0)]
    # velocities2 = [Point2D(0.0, 0.0), Point2D(0.0, 0.0)] #, Point2D(0.0,0.0)]
    # angles2 = [0.6, 0.8] #, 0.5]

    # particles2 = [Particle(0, points2[n], angles2[n], velocities2[n]) for n in range(0, len(points2))]


    # x = np.arange(-bx/4.0, bx/4.0, 4.0)
    # points3 = [Point2D(x[n],x[n]) for n in range(0, len(x))]

    points3 = [Point2D(-5.0, 5.0), Point2D(-1.0, 5.0), Point2D(3.0, 5.0), \
               Point2D(-5.0, 1.0), Point2D(-1.0, 1.0), Point2D(3.0, 1.0), \
               Point2D(-5.0,  -3.0), Point2D(-1.0, -3.0), Point2D(3.0, -3.0)]
    
    # points3 = [Point2D(-4.4027139363549, -6.495108477059635), Point2D(-2.169136010721031, -0.4643194028135213), Point2D(3.123386088406032, -3.3947349523559636)]

    # points3 = [Point2D(0.0, 0.0), Point2D(5.0, 0.0)]#, Point2D(3.0, -5.0)] #\

    velocities3 = [ Point2D(0.0, 0.0) for n in range(0, len(points3)) ]
    angles3 = [random.randreal(-math.pi, math.pi) for n in range(0, len(points3))]
    # angles3 = [0.0, -math.pi]

    # particles3 = [Particle(0, points3[n], angles3[n], velocities3[n]) for n in range(0, len(points3))]


    for p in particles:
        system.addParticle(p)
    
    evolver = Evolver(system)
    evolver.setTimeStep(dt)

    selfProp = {"alpha" : 0.5}
    vicsekParams = {"rcut" : 1.0, "k" : 0.4}
    integratorActiveParams = {"Dpos": 1.0, "Drot" : 1.0, "gammaPos" : 1.0, "gammaRot" : 1.0, "hasNoise" : True}
    integratorParams = {"dzetaPos" : 15.4, "dzetaRot" : -0.38, 
                        "gammaPos" : 1.0, "gammaRot" : 1.0,
                        "Dc"       : 4.0, "k"        : 0.5, "c0" : 1.0,
                        "dr"       : 0.001, "pe"       : 12,   "hasNoise" : True, "delta" : 0.3}

    wcaParams = { "epsilon" : 2.0, "sigma" : 2.0, "dr" : 0.001, "rcut" : 2.25}
                        

    #evolver.addForce("WCA", wcaParams)
    evolver.addForce("SelfPropulsionForce", selfProp)
    evolver.addTorque("PolarAlignment", vicsekParams)
    evolver.setGlobalRcut(vicsekParams["rcut"])
    
    #evolver.addIntegrator("ChemActiveIntegrator", integratorParams)
    evolver.addIntegrator("ActiveMatterIntegrator", integratorActiveParams)
    
    msd = []
    time = []

    ref = system.getParticles()

    print("==== evolution started =====")
    print(f"number of particles: {N}")

    for n in range(20000):
        # print(f"=================step {n} started================")
        # print(len(system.getParticles()))

        for p in system.getParticles():
            # print(f"position {p.id}: {p.r.x} {p.r.y}")
            # print(f"force {p.id}: {p.f.x} {p.f.y}")
            # print(f"neighbors {p.id}: {system.getNeighbors()[p.id]}")
            assert - size.x / 2.0 <= p.r.x <= size.x / 2.0, f"particle {p.id} outside box in x: {p.r.x}"
            assert - size.y / 2.0 <= p.r.y <= size.y / 2.0, f"particle {p.id} outside box in y!"

        evolver.evolve()


        # print(f"=================step {n} done===================")

        if (n%100 == 0):
            print(n)
            time.append(math.log10(n + 0.1))
            msd.append(math.log10(calculateMSD(system.getParticles(), ref)))
            dump_vtp(system.getParticles(), f"data/t={n}.vtp")
            

    msd.pop(0)
    time.pop(0)

    print("=====done=====")
    plt.scatter(time, msd)
    plt.savefig("msd.png")
    # print(f"number of particles: {N}")
    
                


if __name__ == "__main__":
        main()


