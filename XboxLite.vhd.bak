

library ieee;
use ieee.std_logic_1164.all;
use ieee.STD_LOGIC_ARITH.all;
use IEEE.std_logic_unsigned.all;

entity XboxLite is
port (
	LDR_sen , clk : in STD_Logic;
	onJump_sen  : in STD_LOGIC;
	sevenSeg :  out std_logic_vector(15 downto 0);
	pwm_motor , LED_out  : out STD_LOGIC);
END XboxLite;

architecture behaviour of XboxLite is 
	Component CounterOn
		port(jump : in std_logic;
		num : out std_logic_vector(15 downto 0));
	end Component;	
	
	Component MotorCTRL
				PORT(clk, sen_in : IN STD_LOGIC;
				pwm: OUT STD_LOGIC);
	END Component;
	Begin
	stage0 : CounterOn port map(onJump_sen , sevenSeg );
	stage1 : MotorCTRL port map (clk => clk , sen_in => onJump_sen , pwm => pwm_motor );
	LED_out <= LDR_sen;

End behaviour;

--------------------------- Counter implementation ---------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.STD_LOGIC_ARITH.all;
use IEEE.std_logic_unsigned.all;

entity CounterOn is
port(jump : in std_logic;
num : out std_logic_vector(15 downto 0));
end CounterOn;

architecture arch of CounterOn is
signal tmp : std_logic_vector(7 downto 0):= "00000000";
component convertBCD  
port (s : IN STD_LOGIC_vector (3 downto 0);
O : OUT STd_logic_vector( 7 downto 0));
end component;
begin
process(jump)
begin
if (jump = '1') then
if(tmp(3 downto 0)<9) then
tmp<=tmp+1;
else
tmp<=(tmp(7 downto 4)+1)&"0000";
end if;
end if;
end process;

stage0 : convertBCD port map(tmp(3 downto 0),num(7 downto 0));
stage1 : convertBCD port map(tmp(7 downto 4),num(15 downto 8));

end arch;


--------------------- 7 seg counter conversion ---------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity convertBCD is 
port (s : IN STD_LOGIC_vector (3 downto 0);
O : OUT STd_logic_vector( 7 downto 0));
end convertBCD;

architecture fn_convertBCD of convertBCD is 
begin
with s select   
O<= "00000011" when "0000",
"10011111" when "0001",
"00100101" when "0010",
"00001101" when "0011",
"10011001" when "0100",
"01001001" when "0101",
"01000001" when "0110",
"00011111" when "0111",
"00000001" when "1000",
"00001001" when "1001",
"11111111" when others;
end fn_convertBCD;







--------------------------------- Servo Motor Control --------------------------
library ieee;
use ieee.std_logic_1164.all;

ENTITY MotorCTRL IS
	PORT(clk, sen_in : IN STD_LOGIC;
			pwm: OUT STD_LOGIC);
END MotorCTRL;

ARCHITECTURE main OF MotorCTRL IS

constant clk_hz : real := 10.0e6; -- Lattice iCEstick clock
  constant pulse_hz : real := 50.0;
  constant min_pulse_us : real := 500.0; -- TowerPro SG90 values
  constant max_pulse_us : real := 2500.0; -- TowerPro SG90 values
  constant step_bits : positive := 8; -- 0 to 255
  constant step_count : positive := 2**step_bits;
  signal position : integer range 0 to step_count - 1;
  signal motor_ctrl : std_logic := '0';

BEGIN
	
	motor_ctrl <= not sen_in;
	position <= 0 when motor_ctrl = '0' else  85;
	
	SERVO : entity work.servo(rtl)
		generic map (
		clk_hz => clk_hz,
		pulse_hz => pulse_hz,
		min_pulse_us => min_pulse_us,
		max_pulse_us => max_pulse_us,
		step_count => step_count
	)
	port map (
		clk => clk,
		rst => '0',
		position => position,
		pwm => pwm
	);	

	
END main;


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.round;

entity servo is
  generic (
    clk_hz : real;
    pulse_hz : real; -- PWM pulse frequency
    min_pulse_us : real; -- uS pulse width at min position
    max_pulse_us : real; -- uS pulse width at max position
    step_count : positive -- Number of steps from min to max
  );
  port (
    clk : in std_logic;
    rst : in std_logic;
    position : in integer range 0 to step_count - 1;
    pwm : out std_logic
  );
end servo;

architecture rtl of servo is

  -- Number of clock cycles in <us_count> Microseconds
  function cycles_per_us (us_count : real) return integer is
  begin
    return integer(round(clk_hz / 1.0e6 * us_count));
  end function;

  constant min_count : integer := cycles_per_us(min_pulse_us);
  constant max_count : integer := cycles_per_us(max_pulse_us);
  constant min_max_range_us : real := max_pulse_us - min_pulse_us;
  constant step_us : real := min_max_range_us / real(step_count - 1);
  constant cycles_per_step : positive := cycles_per_us(step_us);

  constant counter_max : integer := integer(round(clk_hz / pulse_hz)) - 1;
  signal counter : integer range 0 to counter_max;

  signal duty_cycle : integer range 0 to max_count;

begin

  COUNTER_PROC : process(clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        counter <= 0;

      else
        if counter < counter_max then
          counter <= counter + 1;
        else
          counter <= 0;
        end if;

      end if;
    end if;
  end process;

  PWM_PROC : process(clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        pwm <= '0';

      else
        pwm <= '0';

        if counter < duty_cycle then
          pwm <= '1';
        end if;

      end if;
    end if;
  end process;

  DUTY_CYCLE_PROC : process(clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        duty_cycle <= min_count;

      else
        duty_cycle <= position * cycles_per_step + min_count;

      end if;
    end if;
  end process;

end architecture;