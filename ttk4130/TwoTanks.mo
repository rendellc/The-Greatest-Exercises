within ;
package TwoTanks
  model TwoTanks_basic
    constant Real pi = 3.14;
    constant Real g = 9.81;
    // Parameters
    parameter Real A1 = 1.0 "Area of tank 1";
    parameter Real A2 = 2.0 "Area of tank 2";
    parameter Real L = 0.1 "Pipe length";
    parameter Real D = 0.2 "Pipe diameter";
    parameter Real rho = 0.2 "Fluid density";
    parameter Real mu = 2e-3 "Fluid dynamic viscosity";
    // Variables
    Real p1 "Pressure in tank 1";
    Real p2 "Pressure in tank 2";
    Real h1 "Liquid level in tank 1";
    Real h2 "Liquid level in tank 2";
    Real q "Volume flow rate between tanks";
  initial equation
    h1 = 10.0;
    h2 = 0.0;
  equation
    // Relation between pressure and height
    p1 = rho * g * h1;
    p2 = rho * g * h2;
    // Flow between tanks (positive out of tank 1)
    q = (p1 - p2) * pi * D ^ 4 / (128 * mu * L);
    // Mass balances for each tank
    A1 * der(h1) = -q;
    A2 * der(h2) = q;
    annotation (
      Icon(coordinateSystem(preserveAspectRatio = false)),
      Diagram(coordinateSystem(preserveAspectRatio = false)));
  end TwoTanks_basic;

  model TwoTanks_SI
    import SI = Modelica.SIunits;
    // Constants
    constant Real pi = Modelica.Constants.pi;
    constant Real g = Modelica.Constants.g_n;
    // Parameters
    parameter SI.Area A1 = 1.0 "Area of tank 1";
    parameter SI.Area A2 = 2.0 "Area of tank 2";
    parameter SI.Length L = 0.1 "Pipe length";
    parameter SI.Length D = 0.2 "Pipe diameter";
    parameter SI.Density rho = 0.2 "Fluid density";
    parameter SI.DynamicViscosity mu = 2e-3 "Fluid dynamic viscosity";
    // Variables
    SI.Pressure p1 "Pressure in tank 1";
    SI.Pressure p2 "Pressure in tank 2";
    SI.Length h1 "Liquid level in tank 1";
    SI.Length h2 "Liquid level in tank 2";
    SI.VolumeFlowRate q "Volume flow rate between tanks";
  initial equation
    h1 = 10.0;
    h2 = 0.0;
  equation
    // Relation between pressure and height
    p1 = rho * g * h1;
    p2 = rho * g * h2;
    // Flow between tanks (positive out of tank 1)
    q = (p1 - p2) * pi * D ^ 4 / (128 * mu * L);
    // Mass balances for each tank
    A1 * der(h1) = -q;
    A2 * der(h2) = q;
  end TwoTanks_SI;

  connector FlowPort
    import SI = Modelica.SIunits;
    flow SI.VolumeFlowRate q
      "Volume flow rate from connection point into component";
    SI.Pressure p "Thermodynamic pressure in the connection point";
  end FlowPort;

  model Tank
    import SI = Modelica.SIunits;
    // constants
    constant Real g = Modelica.Constants.g_n;
    constant Real pi = Modelica.Constants.pi;
    // parameter
    parameter SI.Area A = 1.0 "Area of tank";
    parameter SI.Density rho = 0.2 "Fluid density";
    parameter SI.Length h0 = 0.0 "Initial area of liquid level";
    // Ports
    FlowPort flowport "fluid flows in or out of tank";
    // Variables
    SI.Pressure p "Pressure in tank";
    SI.Length h "Height of liquid level";
  initial equation
    h = h0;
  equation
    // Relating pressure and height
    p = rho * g * h;
    // Mass balance
    A * der(h) = -flowport.q;
    flowport.p = p;
  end Tank;

  model Pipe
    import SI = Modelica.SIunits;
    // Constants
    constant Real pi = Modelica.Constants.pi;
    // Parameters
    parameter SI.Length L = 1.0 "Length of pipe";
    parameter SI.Length D = 0.2 "Diameter of pipe";
    parameter SI.DynamicViscosity mu = 2e-3 "Fluid Dynamic Viscosity";
    // Connectors
    FlowPort port1;
    FlowPort port2;
  equation
    port2.q = (port1.p - port2.p) * pi * D ^ 4 / (128 * mu * L);
    port1.q = -port2.q;
  end Pipe;

  model TwoTanks
    Tank tank1(A = 1.0, h0 = 1.0);
    Tank tank2(A = 2.0, h0 = 10.0);
    Pipe pipe(L = 0.1, D = 0.2, mu = 2e-3);
  equation
    connect(tank1.flowport, pipe.port1);
    connect(tank2.flowport, pipe.port2);
  end TwoTanks;

  model TwoTanks_withfluid
    Modelica.Fluid.Pipes.StaticPipe pipe(redeclare package Medium =
          Modelica.Media.Water.ConstantPropertyLiquidWater,                                                           length = 0.1, diameter = 0.2, redeclare
        model FlowModel =
          Modelica.Fluid.Pipes.BaseClasses.FlowModels.DetailedPipeFlow,
      allowFlowReversal=true)                                                                                                     annotation (
      Placement(visible = true, transformation(origin = {-2, -12}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Modelica.Fluid.Vessels.OpenTank tank1(redeclare package Medium =
          Modelica.Media.Water.ConstantPropertyLiquidWater,                                                            crossArea = 1.0, height = 100,             use_portsData = false,
      nPorts=1)                                                                                                     annotation (
      Placement(visible = true, transformation(origin = {-60, 20}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
    Modelica.Fluid.Vessels.OpenTank tank2(redeclare package Medium =
          Modelica.Media.Water.ConstantPropertyLiquidWater,                                                            crossArea = 2.0, height = 100, nPorts=1,   use_portsData = false) annotation (
      Placement(visible = true, transformation(origin = {60, 20}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
    inner Modelica.Fluid.System system annotation (
      Placement(visible = true, transformation(origin = {-2, 68}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  equation
    connect(tank1.ports[1], pipe.port_a) annotation (Line(points={{-60,0},{-52,
            0},{-52,-12},{-12,-12}}, color={0,127,255}));
    connect(tank2.ports[1], pipe.port_b) annotation (Line(points={{60,0},{60,0},
            {60,-12},{8,-12},{8,-12}}, color={0,127,255}));
  end TwoTanks_withfluid;
  annotation (
    uses(Modelica(version = "3.2.1")));
end TwoTanks;
