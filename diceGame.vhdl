library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DiceGameEDA3000 is
	port(CLK : in std_logic;  Reset : in std_logic;  Push1, Push2 : in std_logic;
		Muxcnt : out std_logic_vector(1 to 6);  Seg7 : out std_logic_vector(6 downto 0);
		Led : out std_logic_vector(7 downto 0));
end DiceGameEDA3000;

architecture Behavioral of DiceGameEDA3000 is
---------------------------------------------------
	component ClockDown 
		generic(Mainclk : integer := 50000000; OutCLK : positive := 1000);
		port (CLK : in std_logic;  Reset : in std_logic;  CLKOut : out std_logic);
	end component;
---------------------------------------------------
	component Int2Seg7 
		port(	CLK : in std_logic;  IntNum : in integer range 1 to 6;
			Seg7 : out std_logic_vector(6 downto 0));
	end component;
---------------------------------------------------
	component Diceroller 
		port(CLK, Roll, Reset : in std_logic;  DiceA, DiceB : out integer range 1 to 6;
			Sum : out integer range 2 to 12);
	end component;
---------------------------------------------------
	component Debounce 
		port(CLK : in std_logic;  Reset : in std_logic;  SWIn : in std_logic;
			SWOut : out std_logic);
	end component;
---------------------------------------------------
	component ModCount6 
		port(CLK : in std_logic;  Reset : in std_logic;  OutVal : out integer range 1 to 6);
	end component;
---------------------------------------------------
	signal ICLK : std_logic := '0';
	signal IPush1, IPush2 : std_logic := '0';
	signal Roll1, Roll2 : std_logic := '1';
	signal IVal1, IVal2, IVal5, IVal6 : integer range 1 to 6 :=1;
	signal ISeg1, ISeg2, ISeg3, ISeg4, ISeg5, ISeg6 : std_logic_vector(6 downto 0);
	signal ISel : integer range 1 to 6;
	signal ISum1, ISum2 : integer range 2 to 12 := 2;
	signal IState : integer range 0 to 1;
	signal Done : std_logic := '0';
----------------------------------------------------------------------
begin
	ISeg3 <= "0000000";  ISeg4 <= "0000000";
U1 : ClockDown
	generic map(50000000, 1000) port map (CLK, Reset, ICLK);
U2 : ModCount6
	port map (ICLK, Reset, ISel);
U3 : Debounce 
	port map(ICLK, Reset, Push1, IPush1);
U4 : Debounce 
	port map(ICLK, Reset, Push2, IPush2);	
U5 : Diceroller
	port map (ICLK, Roll1, Reset, IVal1, IVal2, ISum1);
U6 : Diceroller
	port map (ICLK, Roll2, Reset, IVal5, IVal6, ISum2);
U7 : Int2Seg7
	port map (ICLK, IVal1, ISeg1);
U8 : Int2Seg7
	port map (ICLK, IVal2, ISeg2);
U9	: Int2Seg7
	port map (ICLK, IVal5, ISeg5);
U10 : Int2Seg7
	port map (ICLK, IVal6, ISeg6);
----------------------------------------------------------------------
	process(ICLK, Reset, IState, IPush1, IPush2, ISum1, ISum2)
	begin
		Done <= '0';  Roll1 <= '1';  Roll2 <= '1';
		case IState is
			when 0 =>
				if(IPush1 = '0'  ) then Led <= "11111111"; 
					if Done = '0' then Roll1 <= '0'; 
					end if; 
				elsif (ISum1 = 7 or ISum1 = 11) then Led <= "10000000"; Done <= '1';
					if (Reset = '0') then Led <= "00000000"; IState <= 0;
					end if;
				elsif (ISum1 = 2 or ISum1 = 3 or ISum1 = 12) then 
Led <= "00000001"; Done <= '1'; 
					if (Reset = '0') then Led <= "00000000"; IState <= 0;
					end if;
				else Led <= "00011000"; IState <= 1; Done <= '0';
					if (Reset = '0') then Led <= "00000000"; IState <= 0;
					end if;
				end if;
			when 1 =>
				if(IPush2 = '0' and Done = '0') then Led <= "11111111"; Roll2 <= '0';
				elsif (ISum1 = ISum2) then Led <= "10000000"; Done <= '1'; 
					if (Reset = '0') then Led <= "00000000"; IState <= 0;
					end if;
				elsif (ISum2 = 7) then Led <= "00000001"; Done <= '1';
					if (Reset = '0') then Led <= "00000000"; IState <= 0;
					end if;
				else Led <= "00011000"; Done <= '0'; IState <= 1;
					if (Reset = '0') then Led <= "00000000"; IState <= 0;
					end if;
				end if;
			when others => 
					if (Reset = '0') then Led <= "00000000"; IState <= 0;
					end if;
		end case;
	end process;
----------------------------------------------------------------------
	process(ICLK, ISel, ISeg1, ISeg2, ISeg5, ISeg6)
	begin
		if ICLK'event and ICLK = '1' then
			case Isel is
				when 1 => Muxcnt <= "100000"; Seg7 <= ISeg1;
				when 2 => Muxcnt <= "010000"; Seg7 <= ISeg2;
				when 3 => Muxcnt <= "001000"; Seg7 <= ISeg3;
				when 4 => Muxcnt <= "000100"; Seg7 <= ISeg4;
				when 5 => Muxcnt <= "000010"; Seg7 <= ISeg5;
				when 6 => Muxcnt <= "000001"; Seg7 <= ISeg6;
				when others => Muxcnt <= "000000"; Seg7 <= "1111111";
			end case;
		end if;
	end process;
end Behavioral;
--------------------------------------------------------------------------

entity DiceRoller is
	port(CLK, Roll, Reset : in std_logic;  DiceA, DiceB : out integer range 1 to 6;
		Sum : out integer range 2 to 12);
end DiceRoller;

architecture Behavioral of DiceRoller is
	signal Dice1, Dice2 : integer range 1 to 6 := 1;	
begin
	process(CLK, Roll, Reset)
	begin
		if(Reset = '0') then Dice1 <= 1; Dice2 <= 1;
		elsif (CLK'event and CLK = '1') then
			if Roll='0' then
				if Dice1 = 6 then Dice1 <= 1; 
				else Dice1 <= Dice1 + 1; 
				end if;
				if Dice1 = 6 then
					if Dice2 = 6 then Dice2 <= 1; 
					else Dice2 <= Dice2 + 1; 
					end if;
				end if;
			end if;
		end if;
	end process;
	DiceA <= Dice1;
	DiceB <= Dice2;
	Sum <= Dice1 + Dice2 when Roll = '1';
end Behavioral;
--------------------------------------------------------------------------

entity Int2Seg7 is
	port(	CLK : in std_logic;  IntNum : in integer range 1 to 6;
		Seg7 : out std_logic_vector(6 downto 0));
end Int2Seg7;

architecture Behavioral of Int2Seg7 is
begin
	process(CLK, IntNum)
	begin
		if CLK'event and CLK = '1' then
			if   (IntNum = 1) then Seg7 <= "0000110"; --gfedcba
			elsif(IntNum = 2) then Seg7 <= "1011011";
			elsif(IntNum = 3) then Seg7 <= "1001111";
			elsif(IntNum = 4) then Seg7 <= "1100110";
			elsif(IntNum = 5) then Seg7 <= "1101101";
			else 				Seg7 <= "1111101";
			end if;
		end if;
	end process;
end Behavioral;
--------------------------------------------------------------------------

entity ModCount6 is
	port(CLK : in std_logic;  Reset : in std_logic;  OutVal : out integer range 1 to 6);
end ModCount6;

architecture Behavioral of ModCount6 is
	signal IVal : integer range 1 to 6;
begin
	process(CLK, Reset, IVal)
	begin
		if (Reset = '0') then IVal <= 1;
		elsif (CLK'event and CLK = '1') then 
			if (IVal = 6) then
				IVal <= 1;
			else
				IVal <= IVal + 1;
			end if;
		end if;
	end process;
	OutVal <= IVal;
end Behavioral;
--------------------------------------------------------------------------

entity ClockDown is
	generic(Mainclk : integer := 50000000; OutCLK : positive := 1000);
	port (CLK : in std_logic;  Reset : in std_logic;  CLKOut : out std_logic);
end ClockDown;

architecture Behavioral of ClockDown is
	constant CLKCntVal : integer := ((Mainclk/OutCLK)/2)-1;
begin
	process(CLK, Reset)
		variable CLKCnt : integer range 0 to CLKCntVal :=0;
		variable ICLK : std_logic := '0';
	begin
		if (Reset = '0')then
			CLKCnt := 0;  ICLK := '0';
		elsif (CLK'event and CLK = '1') then
			if (CLKCnt = CLKCntVal) then
				CLKCnt := 0;  ICLK := not ICLK;
			else  CLKCnt := CLKCnt + 1;
			end if;
		end if;
		CLKOut <= ICLK;
	end process;
end Behavioral;
--------------------------------------------------------------------------

entity Debounce is
	port(CLK : in std_logic;  Reset : in std_logic;  SWIn : in std_logic;  SWOut : out std_logic);
end Debounce;

architecture Behavioral of Debounce is
	signal ISW : std_logic := '0';
begin
	process(CLK, Reset, SWIn)
	begin
		if (Reset = '0') then
			SWOut <= '1';                -- switch : active low, steady state : high
			ISW <= '1';                   -- switch : active low, steady state : high
		elsif (CLK'event and CLK = '1') then
			ISW <= SWIn;  SWOut <= ISW;
		end if;
	end process;
end Behavioral;
--------------------------------------------------------------------------
