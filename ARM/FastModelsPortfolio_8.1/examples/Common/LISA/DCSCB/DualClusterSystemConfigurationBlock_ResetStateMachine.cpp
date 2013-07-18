
#include "DualClusterSystemConfigurationBlock_ResetStateMachine.h"

#include <sstream>

namespace
{
    void replace( std::string& o, std::string const& arg1, std::string const& arg2 )
    {
        std::string::size_type i = 0;
        while ( (i = o.find(arg1, i)) != std::string::npos )
        {
            o.replace( i, arg1.length(), arg2 );
            i += arg2.length();
        }
    }

    std::string cify( std::string const& str_ )
    {
        std::string output( str_ );
        replace( output, "\\", "\\\\" );
        replace( output, "\t", "\\t" );
        replace( output, "\"", "\\\"" );
        replace( output, "\n", "\\n\"\n\t\"" );

        output.insert( 0, "\t\"" );
        output += '"';

        return output;
    }

    void assert_same(
        char const*          filename_,
        unsigned             line_number_,
        char const*          func,
        std::ostringstream&  os_,
        std::string const    expected_
        )
    {
        if (os_.str() != expected_)
        {
            std::cerr << "\n\n----------------------------------------------------------------------\n"
                      << filename_ << ":" << line_number_ << ":" << func << ": ERROR!\n"
                      << "Expected:-\n" << cify(expected_) << "\n"
                      << "----------------------------------------------------------------------\n"
                      << "Got:-\n" << cify(os_.str()) << "\n"
                      << "----------------------------------------------------------------------\n\n"
                ;
            assert(0);
        }
    }

#define ASSERT_SAME( OS, EXPECTED )                             \
    assert_same( __FILE__, __LINE__, __func__, OS, EXPECTED )

    void test_display_dcs_leds()
    {
        std::ostringstream os;
        for (unsigned i = 0; i <= 0xFF; ++ i)
        {
            DCSCBDetails::display_dcs_leds( os, i );
        }

        ASSERT_SAME(
            os,
            "DCS_LEDS [ ........ ]\n"
            "DCS_LEDS [ .......O ]\n"
            "DCS_LEDS [ ......O. ]\n"
            "DCS_LEDS [ ......OO ]\n"
            "DCS_LEDS [ .....O.. ]\n"
            "DCS_LEDS [ .....O.O ]\n"
            "DCS_LEDS [ .....OO. ]\n"
            "DCS_LEDS [ .....OOO ]\n"
            "DCS_LEDS [ ....O... ]\n"
            "DCS_LEDS [ ....O..O ]\n"
            "DCS_LEDS [ ....O.O. ]\n"
            "DCS_LEDS [ ....O.OO ]\n"
            "DCS_LEDS [ ....OO.. ]\n"
            "DCS_LEDS [ ....OO.O ]\n"
            "DCS_LEDS [ ....OOO. ]\n"
            "DCS_LEDS [ ....OOOO ]\n"
            "DCS_LEDS [ ...O.... ]\n"
            "DCS_LEDS [ ...O...O ]\n"
            "DCS_LEDS [ ...O..O. ]\n"
            "DCS_LEDS [ ...O..OO ]\n"
            "DCS_LEDS [ ...O.O.. ]\n"
            "DCS_LEDS [ ...O.O.O ]\n"
            "DCS_LEDS [ ...O.OO. ]\n"
            "DCS_LEDS [ ...O.OOO ]\n"
            "DCS_LEDS [ ...OO... ]\n"
            "DCS_LEDS [ ...OO..O ]\n"
            "DCS_LEDS [ ...OO.O. ]\n"
            "DCS_LEDS [ ...OO.OO ]\n"
            "DCS_LEDS [ ...OOO.. ]\n"
            "DCS_LEDS [ ...OOO.O ]\n"
            "DCS_LEDS [ ...OOOO. ]\n"
            "DCS_LEDS [ ...OOOOO ]\n"
            "DCS_LEDS [ ..O..... ]\n"
            "DCS_LEDS [ ..O....O ]\n"
            "DCS_LEDS [ ..O...O. ]\n"
            "DCS_LEDS [ ..O...OO ]\n"
            "DCS_LEDS [ ..O..O.. ]\n"
            "DCS_LEDS [ ..O..O.O ]\n"
            "DCS_LEDS [ ..O..OO. ]\n"
            "DCS_LEDS [ ..O..OOO ]\n"
            "DCS_LEDS [ ..O.O... ]\n"
            "DCS_LEDS [ ..O.O..O ]\n"
            "DCS_LEDS [ ..O.O.O. ]\n"
            "DCS_LEDS [ ..O.O.OO ]\n"
            "DCS_LEDS [ ..O.OO.. ]\n"
            "DCS_LEDS [ ..O.OO.O ]\n"
            "DCS_LEDS [ ..O.OOO. ]\n"
            "DCS_LEDS [ ..O.OOOO ]\n"
            "DCS_LEDS [ ..OO.... ]\n"
            "DCS_LEDS [ ..OO...O ]\n"
            "DCS_LEDS [ ..OO..O. ]\n"
            "DCS_LEDS [ ..OO..OO ]\n"
            "DCS_LEDS [ ..OO.O.. ]\n"
            "DCS_LEDS [ ..OO.O.O ]\n"
            "DCS_LEDS [ ..OO.OO. ]\n"
            "DCS_LEDS [ ..OO.OOO ]\n"
            "DCS_LEDS [ ..OOO... ]\n"
            "DCS_LEDS [ ..OOO..O ]\n"
            "DCS_LEDS [ ..OOO.O. ]\n"
            "DCS_LEDS [ ..OOO.OO ]\n"
            "DCS_LEDS [ ..OOOO.. ]\n"
            "DCS_LEDS [ ..OOOO.O ]\n"
            "DCS_LEDS [ ..OOOOO. ]\n"
            "DCS_LEDS [ ..OOOOOO ]\n"
            "DCS_LEDS [ .O...... ]\n"
            "DCS_LEDS [ .O.....O ]\n"
            "DCS_LEDS [ .O....O. ]\n"
            "DCS_LEDS [ .O....OO ]\n"
            "DCS_LEDS [ .O...O.. ]\n"
            "DCS_LEDS [ .O...O.O ]\n"
            "DCS_LEDS [ .O...OO. ]\n"
            "DCS_LEDS [ .O...OOO ]\n"
            "DCS_LEDS [ .O..O... ]\n"
            "DCS_LEDS [ .O..O..O ]\n"
            "DCS_LEDS [ .O..O.O. ]\n"
            "DCS_LEDS [ .O..O.OO ]\n"
            "DCS_LEDS [ .O..OO.. ]\n"
            "DCS_LEDS [ .O..OO.O ]\n"
            "DCS_LEDS [ .O..OOO. ]\n"
            "DCS_LEDS [ .O..OOOO ]\n"
            "DCS_LEDS [ .O.O.... ]\n"
            "DCS_LEDS [ .O.O...O ]\n"
            "DCS_LEDS [ .O.O..O. ]\n"
            "DCS_LEDS [ .O.O..OO ]\n"
            "DCS_LEDS [ .O.O.O.. ]\n"
            "DCS_LEDS [ .O.O.O.O ]\n"
            "DCS_LEDS [ .O.O.OO. ]\n"
            "DCS_LEDS [ .O.O.OOO ]\n"
            "DCS_LEDS [ .O.OO... ]\n"
            "DCS_LEDS [ .O.OO..O ]\n"
            "DCS_LEDS [ .O.OO.O. ]\n"
            "DCS_LEDS [ .O.OO.OO ]\n"
            "DCS_LEDS [ .O.OOO.. ]\n"
            "DCS_LEDS [ .O.OOO.O ]\n"
            "DCS_LEDS [ .O.OOOO. ]\n"
            "DCS_LEDS [ .O.OOOOO ]\n"
            "DCS_LEDS [ .OO..... ]\n"
            "DCS_LEDS [ .OO....O ]\n"
            "DCS_LEDS [ .OO...O. ]\n"
            "DCS_LEDS [ .OO...OO ]\n"
            "DCS_LEDS [ .OO..O.. ]\n"
            "DCS_LEDS [ .OO..O.O ]\n"
            "DCS_LEDS [ .OO..OO. ]\n"
            "DCS_LEDS [ .OO..OOO ]\n"
            "DCS_LEDS [ .OO.O... ]\n"
            "DCS_LEDS [ .OO.O..O ]\n"
            "DCS_LEDS [ .OO.O.O. ]\n"
            "DCS_LEDS [ .OO.O.OO ]\n"
            "DCS_LEDS [ .OO.OO.. ]\n"
            "DCS_LEDS [ .OO.OO.O ]\n"
            "DCS_LEDS [ .OO.OOO. ]\n"
            "DCS_LEDS [ .OO.OOOO ]\n"
            "DCS_LEDS [ .OOO.... ]\n"
            "DCS_LEDS [ .OOO...O ]\n"
            "DCS_LEDS [ .OOO..O. ]\n"
            "DCS_LEDS [ .OOO..OO ]\n"
            "DCS_LEDS [ .OOO.O.. ]\n"
            "DCS_LEDS [ .OOO.O.O ]\n"
            "DCS_LEDS [ .OOO.OO. ]\n"
            "DCS_LEDS [ .OOO.OOO ]\n"
            "DCS_LEDS [ .OOOO... ]\n"
            "DCS_LEDS [ .OOOO..O ]\n"
            "DCS_LEDS [ .OOOO.O. ]\n"
            "DCS_LEDS [ .OOOO.OO ]\n"
            "DCS_LEDS [ .OOOOO.. ]\n"
            "DCS_LEDS [ .OOOOO.O ]\n"
            "DCS_LEDS [ .OOOOOO. ]\n"
            "DCS_LEDS [ .OOOOOOO ]\n"
            "DCS_LEDS [ O....... ]\n"
            "DCS_LEDS [ O......O ]\n"
            "DCS_LEDS [ O.....O. ]\n"
            "DCS_LEDS [ O.....OO ]\n"
            "DCS_LEDS [ O....O.. ]\n"
            "DCS_LEDS [ O....O.O ]\n"
            "DCS_LEDS [ O....OO. ]\n"
            "DCS_LEDS [ O....OOO ]\n"
            "DCS_LEDS [ O...O... ]\n"
            "DCS_LEDS [ O...O..O ]\n"
            "DCS_LEDS [ O...O.O. ]\n"
            "DCS_LEDS [ O...O.OO ]\n"
            "DCS_LEDS [ O...OO.. ]\n"
            "DCS_LEDS [ O...OO.O ]\n"
            "DCS_LEDS [ O...OOO. ]\n"
            "DCS_LEDS [ O...OOOO ]\n"
            "DCS_LEDS [ O..O.... ]\n"
            "DCS_LEDS [ O..O...O ]\n"
            "DCS_LEDS [ O..O..O. ]\n"
            "DCS_LEDS [ O..O..OO ]\n"
            "DCS_LEDS [ O..O.O.. ]\n"
            "DCS_LEDS [ O..O.O.O ]\n"
            "DCS_LEDS [ O..O.OO. ]\n"
            "DCS_LEDS [ O..O.OOO ]\n"
            "DCS_LEDS [ O..OO... ]\n"
            "DCS_LEDS [ O..OO..O ]\n"
            "DCS_LEDS [ O..OO.O. ]\n"
            "DCS_LEDS [ O..OO.OO ]\n"
            "DCS_LEDS [ O..OOO.. ]\n"
            "DCS_LEDS [ O..OOO.O ]\n"
            "DCS_LEDS [ O..OOOO. ]\n"
            "DCS_LEDS [ O..OOOOO ]\n"
            "DCS_LEDS [ O.O..... ]\n"
            "DCS_LEDS [ O.O....O ]\n"
            "DCS_LEDS [ O.O...O. ]\n"
            "DCS_LEDS [ O.O...OO ]\n"
            "DCS_LEDS [ O.O..O.. ]\n"
            "DCS_LEDS [ O.O..O.O ]\n"
            "DCS_LEDS [ O.O..OO. ]\n"
            "DCS_LEDS [ O.O..OOO ]\n"
            "DCS_LEDS [ O.O.O... ]\n"
            "DCS_LEDS [ O.O.O..O ]\n"
            "DCS_LEDS [ O.O.O.O. ]\n"
            "DCS_LEDS [ O.O.O.OO ]\n"
            "DCS_LEDS [ O.O.OO.. ]\n"
            "DCS_LEDS [ O.O.OO.O ]\n"
            "DCS_LEDS [ O.O.OOO. ]\n"
            "DCS_LEDS [ O.O.OOOO ]\n"
            "DCS_LEDS [ O.OO.... ]\n"
            "DCS_LEDS [ O.OO...O ]\n"
            "DCS_LEDS [ O.OO..O. ]\n"
            "DCS_LEDS [ O.OO..OO ]\n"
            "DCS_LEDS [ O.OO.O.. ]\n"
            "DCS_LEDS [ O.OO.O.O ]\n"
            "DCS_LEDS [ O.OO.OO. ]\n"
            "DCS_LEDS [ O.OO.OOO ]\n"
            "DCS_LEDS [ O.OOO... ]\n"
            "DCS_LEDS [ O.OOO..O ]\n"
            "DCS_LEDS [ O.OOO.O. ]\n"
            "DCS_LEDS [ O.OOO.OO ]\n"
            "DCS_LEDS [ O.OOOO.. ]\n"
            "DCS_LEDS [ O.OOOO.O ]\n"
            "DCS_LEDS [ O.OOOOO. ]\n"
            "DCS_LEDS [ O.OOOOOO ]\n"
            "DCS_LEDS [ OO...... ]\n"
            "DCS_LEDS [ OO.....O ]\n"
            "DCS_LEDS [ OO....O. ]\n"
            "DCS_LEDS [ OO....OO ]\n"
            "DCS_LEDS [ OO...O.. ]\n"
            "DCS_LEDS [ OO...O.O ]\n"
            "DCS_LEDS [ OO...OO. ]\n"
            "DCS_LEDS [ OO...OOO ]\n"
            "DCS_LEDS [ OO..O... ]\n"
            "DCS_LEDS [ OO..O..O ]\n"
            "DCS_LEDS [ OO..O.O. ]\n"
            "DCS_LEDS [ OO..O.OO ]\n"
            "DCS_LEDS [ OO..OO.. ]\n"
            "DCS_LEDS [ OO..OO.O ]\n"
            "DCS_LEDS [ OO..OOO. ]\n"
            "DCS_LEDS [ OO..OOOO ]\n"
            "DCS_LEDS [ OO.O.... ]\n"
            "DCS_LEDS [ OO.O...O ]\n"
            "DCS_LEDS [ OO.O..O. ]\n"
            "DCS_LEDS [ OO.O..OO ]\n"
            "DCS_LEDS [ OO.O.O.. ]\n"
            "DCS_LEDS [ OO.O.O.O ]\n"
            "DCS_LEDS [ OO.O.OO. ]\n"
            "DCS_LEDS [ OO.O.OOO ]\n"
            "DCS_LEDS [ OO.OO... ]\n"
            "DCS_LEDS [ OO.OO..O ]\n"
            "DCS_LEDS [ OO.OO.O. ]\n"
            "DCS_LEDS [ OO.OO.OO ]\n"
            "DCS_LEDS [ OO.OOO.. ]\n"
            "DCS_LEDS [ OO.OOO.O ]\n"
            "DCS_LEDS [ OO.OOOO. ]\n"
            "DCS_LEDS [ OO.OOOOO ]\n"
            "DCS_LEDS [ OOO..... ]\n"
            "DCS_LEDS [ OOO....O ]\n"
            "DCS_LEDS [ OOO...O. ]\n"
            "DCS_LEDS [ OOO...OO ]\n"
            "DCS_LEDS [ OOO..O.. ]\n"
            "DCS_LEDS [ OOO..O.O ]\n"
            "DCS_LEDS [ OOO..OO. ]\n"
            "DCS_LEDS [ OOO..OOO ]\n"
            "DCS_LEDS [ OOO.O... ]\n"
            "DCS_LEDS [ OOO.O..O ]\n"
            "DCS_LEDS [ OOO.O.O. ]\n"
            "DCS_LEDS [ OOO.O.OO ]\n"
            "DCS_LEDS [ OOO.OO.. ]\n"
            "DCS_LEDS [ OOO.OO.O ]\n"
            "DCS_LEDS [ OOO.OOO. ]\n"
            "DCS_LEDS [ OOO.OOOO ]\n"
            "DCS_LEDS [ OOOO.... ]\n"
            "DCS_LEDS [ OOOO...O ]\n"
            "DCS_LEDS [ OOOO..O. ]\n"
            "DCS_LEDS [ OOOO..OO ]\n"
            "DCS_LEDS [ OOOO.O.. ]\n"
            "DCS_LEDS [ OOOO.O.O ]\n"
            "DCS_LEDS [ OOOO.OO. ]\n"
            "DCS_LEDS [ OOOO.OOO ]\n"
            "DCS_LEDS [ OOOOO... ]\n"
            "DCS_LEDS [ OOOOO..O ]\n"
            "DCS_LEDS [ OOOOO.O. ]\n"
            "DCS_LEDS [ OOOOO.OO ]\n"
            "DCS_LEDS [ OOOOOO.. ]\n"
            "DCS_LEDS [ OOOOOO.O ]\n"
            "DCS_LEDS [ OOOOOOO. ]\n"
            "DCS_LEDS [ OOOOOOOO ]\n"
            );
    }
}

namespace DCSCBDetails
{

    void test_to_see_if_l2_reset_happens()
    {
        reset_register_handler_t t;// Test case of a single core going down
        
        std::ostringstream os;

        t.init(4,4);

        t.reset(2 ^ 3); // Primary cluster only comes out of reset.

        // Reset to original values.
        t.set_reset_cluster_cfg( 0, 0, 0 );
        t.set_reset_cluster_cfg( 1, 0, 0 );
        t.print_deltas(os); t.reset_deltas_have_been_processed();
        
        os << "About to put CPU2 and CPU3 into WFI mode\n";
        // cluster0.cpu2 in WFI
        t.set_wfi_state( /* cpu_id */ 2, 0, true );
        // cluster0.cpu3 in WFI
        t.set_wfi_state( /* cpu_id */ 3, 0, true );
        t.print_deltas(os); t.reset_deltas_have_been_processed();
        
        os << "Setting RST_HOLD0 to 4\n";
        t.set_rst_hold(0, 0x4);
        t.print_deltas(os); t.reset_deltas_have_been_processed();
        
        os << "Setting RST_HOLD0 to 0\n";
        t.set_rst_hold(0, 0);
        t.print_deltas(os); t.reset_deltas_have_been_processed();
        
        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "debug0-of-1->0\n"
            "debug1-of-1->0\n"
            "debug2-of-1->0\n"
            "debug3-of-1->0\n"
            "cluster0->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            "About to put CPU2 and CPU3 into WFI mode\n"
            "Setting RST_HOLD0 to 4\n"
            "cpu2-of-0->1-Lvt\n"
            "Setting RST_HOLD0 to 0\n"
            "cpu2-of-0->0-Lvt\n"
            );
        os.str("");

    }
    
    void reset_handler_t::tests()
    {
        static bool already_done = false;
        if (already_done)
            return;
        already_done = true;


        test_display_dcs_leds();
        test_to_see_if_l2_reset_happens();
        
        reset_register_handler_t t;

        std::ostringstream os;

        t.init(4,4);

        // Must be before reset() in order for the desired values to be copied
        // in.
        t.set_reset_cluster_cfg( 0, 7, 1 );
        t.set_reset_cluster_cfg( 1, 3, 0 );

        t.reset(2 ^ 3); // Primary cluster only comes out of reset.

        // Reset to original values.
        t.set_reset_cluster_cfg( 0, 0, 0 );
        t.set_reset_cluster_cfg( 1, 0, 0 );

        t.print_deltas(os); t.reset_deltas_have_been_processed();

        os << "Primary cluster should have come out of reset, now pull secondary cluster out by deasserting the rst_hold register\n";

        t.set_rst_hold( 1, 0x0 );


        t.print_deltas(os); t.reset_deltas_have_been_processed();
        os << "     rst_hold/stat = " << std::hex << t.get_rst_hold( 1 ) << "/" << t.get_rst_stat( 1 ) << std::dec << "\n";

        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-7-I\n"
            "cluster1->1-3-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "debug0-of-1->0\n"
            "debug1-of-1->0\n"
            "debug2-of-1->0\n"
            "debug3-of-1->0\n"
            "cluster0->0-7-I\n"
            "system->0\n"
            "sysdebug->0\n"
            "Primary cluster should have come out of reset, now pull secondary cluster out by deasserting the rst_hold register\n"
            "cpu0-of-1->0-Lvt\n"
            "cpu1-of-1->0-Lvt\n"
            "cpu2-of-1->0-Lvt\n"
            "cpu3-of-1->0-Lvt\n"
            "cluster1->0-3-i\n"
            "     rst_hold/stat = 0/0\n"
            );

        os.str("");

        t.reset(2 ^ 3); // Primary cluster only comes out of reset.

        t.print_deltas(os); t.reset_deltas_have_been_processed();

        os << "Now assert a cpu1_poreset through rst_hold0\n";

        t.set_rst_hold( 0, 0x20 );

        t.print_deltas(os); t.reset_deltas_have_been_processed();
        os << "     rst_hold/stat = " << std::hex << t.get_rst_hold( 0 ) << "/" << t.get_rst_stat( 0 ) << std::dec << "\n";

        os << "Now setting WFI state for cpu1\n";
        t.set_wfi_state( /* cpu_id */ 1, /* cluster_id */ 0, true );

        t.print_deltas(os); t.reset_deltas_have_been_processed();
        os << "     rst_hold/stat = " << std::hex << t.get_rst_hold( 0 ) << "/" << t.get_rst_stat( 0 ) << std::dec << "\n";

        os << "Now clearing WFI state for cpu1\n";

        t.set_wfi_state( /* cpu_id */ 1, /* cluster_id */ 0, false );

        t.print_deltas(os); t.reset_deltas_have_been_processed();
        os << "     rst_hold/stat = " << std::hex << t.get_rst_hold( 0 ) << "/" << t.get_rst_stat( 0 ) << std::dec << "\n";

        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "debug0-of-1->0\n"
            "debug1-of-1->0\n"
            "debug2-of-1->0\n"
            "debug3-of-1->0\n"
            "cluster0->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            "Now assert a cpu1_poreset through rst_hold0\n"
            "     rst_hold/stat = 20/0\n"
            "Now setting WFI state for cpu1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "     rst_hold/stat = 20/22\n"
            "Now clearing WFI state for cpu1\n"
            "     rst_hold/stat = 20/22\n"
            );

        os.str("");


        t.reset(2 ^ 3); // Primary cluster only comes out of reset.

        t.print_deltas(os); t.reset_deltas_have_been_processed();

        os << "Now asserting cluster reset through the SYS_SWRESET mechanism\n";

        t.set_sys_swreset( 0x215 );

        t.print_deltas(os); t.reset_deltas_have_been_processed();

        os << "Now turn all of them to WFI state\n";

        t.set_wfi_state( 0, 0, true );
        t.set_wfi_state( 1, 0, true );
        t.set_wfi_state( 2, 0, true );
        t.set_wfi_state( 3, 0, true );

        t.print_deltas(os); t.reset_deltas_have_been_processed();

        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "debug0-of-1->0\n"
            "debug1-of-1->0\n"
            "debug2-of-1->0\n"
            "debug3-of-1->0\n"
            "cluster0->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            "Now asserting cluster reset through the SYS_SWRESET mechanism\n"
            "Now turn all of them to WFI state\n"
            "cpu0-of-0->1-Lvt\n"
            "cpu1-of-0->1-Lvt\n"
            "cpu2-of-0->1-Lvt\n"
            "cpu3-of-0->1-Lvt\n"
            "cluster0->1-0-i\n"
            "cpu0-of-0->0-Lvt\n"
            "cpu1-of-0->0-Lvt\n"
            "cpu2-of-0->0-Lvt\n"
            "cpu3-of-0->0-Lvt\n"
            "cluster0->0-0-i\n"
            );

        os.str("");

        t.reset(0 ^ 3);

        // Should initially generate some resets to set up the original values
        // of the pins.


        t.print_deltas( os );

        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "cpu0-of-1->0-Lvt\n"
            "debug0-of-1->0\n"
            "cpu1-of-1->0-Lvt\n"
            "debug1-of-1->0\n"
            "cpu2-of-1->0-Lvt\n"
            "debug2-of-1->0\n"
            "cpu3-of-1->0-Lvt\n"
            "debug3-of-1->0\n"
            "cluster0->0-0-i\n"
            "cluster1->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();

        t.reset(1 ^ 3);

        t.print_deltas( os );

        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "debug0-of-0->0\n"
            "debug1-of-0->0\n"
            "debug2-of-0->0\n"
            "debug3-of-0->0\n"
            "cpu0-of-1->0-Lvt\n"
            "debug0-of-1->0\n"
            "cpu1-of-1->0-Lvt\n"
            "debug1-of-1->0\n"
            "cpu2-of-1->0-Lvt\n"
            "debug2-of-1->0\n"
            "cpu3-of-1->0-Lvt\n"
            "debug3-of-1->0\n"
            "cluster1->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();

        t.reset(2 ^ 3);

        t.print_deltas( os );

        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "debug0-of-1->0\n"
            "debug1-of-1->0\n"
            "debug2-of-1->0\n"
            "debug3-of-1->0\n"
            "cluster0->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();


        t.reset(2 ^ 3);

        t.print_deltas( os ); t.reset_deltas_have_been_processed();

        os << "About to assert wfi_state\n";

        // Single WFI raised, no reset requests active => does nothing
        t.set_wfi_state( 0, 0, 1 );

        t.print_deltas( os );

        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "debug0-of-1->0\n"
            "debug1-of-1->0\n"
            "debug2-of-1->0\n"
            "debug3-of-1->0\n"
            "cluster0->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            "About to assert wfi_state\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();

        t.reset(0 ^ 3); t.reset_deltas_have_been_processed();

        // We haven't set up any holds or other requests so changing the WFI state should have
        // no effect.
        for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                bool const has_reset_deltas = t.set_wfi_state( cpu_id, cluster_index, true );
                assert( ! has_reset_deltas );
                assert( t.get_reset_deltas().first == t.get_reset_deltas().second );
                t.set_wfi_state( cpu_id, cluster_index, false );
            }

        // Now if we setup a hold register then we should end up with a reset when wfi for
        // that core goes high.

        {
            bool has_reset_deltas;
            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    t.set_rst_hold_cpu_reset( cpu_id, cluster_index, true );
                    // Now to activate the reset then we need to set wfi
                    has_reset_deltas = t.set_wfi_state( cpu_id, cluster_index, true );
                    assert( has_reset_deltas );
                    // And immediately changing it back should continue to hold the reset
                    has_reset_deltas = t.set_wfi_state( cpu_id, cluster_index, false );
                    assert( has_reset_deltas );
                }
            t.print_deltas( os );
            ASSERT_SAME(
                os,
                "cpu0-of-0->1-Lvt\n"
                "cpu0-of-1->1-Lvt\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu3-of-0->1-Lvt\n"
                "cpu3-of-1->1-Lvt\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            // Asserting cluster reset should work immediately as all cores are
            // already in reset.
            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                has_reset_deltas = t.set_rst_hold_cluster_reset( cluster_index, true );
            }

            t.print_deltas( os );

            ASSERT_SAME(
                os,
                "cluster0->1-0-i\n"
                "cluster1->1-0-i\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                has_reset_deltas = t.set_rst_hold_cluster_reset( cluster_index, false );
            }

            t.print_deltas( os );
            ASSERT_SAME(
                os,
                "cluster0->0-0-i\n"
                "cluster1->0-0-i\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            // Now we still have all the core's rst_hold held high, so let's try the
            // same sequence but dropping the hold rst for the cpu reset in between.

            // Asserting cluster reset should work immediately as all cores are
            // already in reset.
            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                has_reset_deltas = t.set_rst_hold_cluster_reset( cluster_index, true );
            }

            t.print_deltas( os ) << " About to deassert cpu_reset on rst_hold...\n";
            t.reset_deltas_have_been_processed();

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    t.set_rst_hold_cpu_reset( cpu_id, cluster_index, false );
                }

            t.print_deltas( os ) << " About to deassert cluster_reset on rst_hold...\n";
            t.reset_deltas_have_been_processed();

            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                has_reset_deltas = t.set_rst_hold_cluster_reset( cluster_index, false );
            }

            t.print_deltas( os );
            ASSERT_SAME(
                os,
                "cluster0->1-0-i\n"
                "cluster1->1-0-i\n"
                " About to deassert cpu_reset on rst_hold...\n"
                " About to deassert cluster_reset on rst_hold...\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cluster0->0-0-i\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cluster1->0-0-i\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            // So now we have all the WFI signals low and all the cores out of reset.

            // We can pulse a reset on each core:
            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os <<  "About to ask for a pulse reset on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    t.set_cpu_reset_req( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os << "Set STANDBYWFI high on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    // Now to activate the reset then we need to set wfi
                    t.set_wfi_state( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os << "And now changing STANDBYWFI back to low...\n";
                    // And immediately changing it back should continue to hold the reset
                    t.set_wfi_state( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            ASSERT_SAME(
                os,
                "About to ask for a pulse reset on cpu0-of-0\n"
                "Set STANDBYWFI high on cpu0-of-0\n"
                "cpu0-of-0->1-Lvt\n"
                "cpu0-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "About to ask for a pulse reset on cpu0-of-1\n"
                "Set STANDBYWFI high on cpu0-of-1\n"
                "cpu0-of-1->1-Lvt\n"
                "cpu0-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "About to ask for a pulse reset on cpu1-of-0\n"
                "Set STANDBYWFI high on cpu1-of-0\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "About to ask for a pulse reset on cpu1-of-1\n"
                "Set STANDBYWFI high on cpu1-of-1\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "About to ask for a pulse reset on cpu2-of-0\n"
                "Set STANDBYWFI high on cpu2-of-0\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "About to ask for a pulse reset on cpu2-of-1\n"
                "Set STANDBYWFI high on cpu2-of-1\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "About to ask for a pulse reset on cpu3-of-0\n"
                "Set STANDBYWFI high on cpu3-of-0\n"
                "cpu3-of-0->1-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "About to ask for a pulse reset on cpu3-of-1\n"
                "Set STANDBYWFI high on cpu3-of-1\n"
                "cpu3-of-1->1-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            //
            // So now we try the same thing but starting with STANDBYWFI high.
            //

            // We can pulse a reset on each core:
            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "Set STANDBYWFI high on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    // Now to activate the reset then we need to set wfi
                    t.set_wfi_state( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os <<  "About to ask for a pulse reset on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    t.set_cpu_reset_req( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os << "And now changing STANDBYWFI back to low...\n";
                    // And immediately changing it back should continue to hold the reset
                    t.set_wfi_state( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            ASSERT_SAME(
                os,
                "Set STANDBYWFI high on cpu0-of-0\n"
                "About to ask for a pulse reset on cpu0-of-0\n"
                "cpu0-of-0->1-Lvt\n"
                "cpu0-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "Set STANDBYWFI high on cpu0-of-1\n"
                "About to ask for a pulse reset on cpu0-of-1\n"
                "cpu0-of-1->1-Lvt\n"
                "cpu0-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "Set STANDBYWFI high on cpu1-of-0\n"
                "About to ask for a pulse reset on cpu1-of-0\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "Set STANDBYWFI high on cpu1-of-1\n"
                "About to ask for a pulse reset on cpu1-of-1\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "Set STANDBYWFI high on cpu2-of-0\n"
                "About to ask for a pulse reset on cpu2-of-0\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "Set STANDBYWFI high on cpu2-of-1\n"
                "About to ask for a pulse reset on cpu2-of-1\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "Set STANDBYWFI high on cpu3-of-0\n"
                "About to ask for a pulse reset on cpu3-of-0\n"
                "cpu3-of-0->1-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                "Set STANDBYWFI high on cpu3-of-1\n"
                "About to ask for a pulse reset on cpu3-of-1\n"
                "cpu3-of-1->1-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "And now changing STANDBYWFI back to low...\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            //
            // So now let's try a cluster reset.
            //
            os << "About to setup a cluster reset...\n";
            t.set_cluster_reset_req( 1, true );
            t.print_deltas(os); t.reset_deltas_have_been_processed();

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "Set STANDBYWFI high on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    // Now to activate the reset then we need to set wfi
                    t.set_wfi_state( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "Set STANDBYWFI low on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    // Now to activate the reset then we need to set wfi
                    t.set_wfi_state( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            ASSERT_SAME(
                os,
                "About to setup a cluster reset...\n"
                "Set STANDBYWFI high on cpu0-of-0\n"
                "Set STANDBYWFI high on cpu0-of-1\n"
                "cpu0-of-1->1-Lvt\n"
                "Set STANDBYWFI high on cpu1-of-0\n"
                "Set STANDBYWFI high on cpu1-of-1\n"
                "cpu1-of-1->1-Lvt\n"
                "Set STANDBYWFI high on cpu2-of-0\n"
                "Set STANDBYWFI high on cpu2-of-1\n"
                "cpu2-of-1->1-Lvt\n"
                "Set STANDBYWFI high on cpu3-of-0\n"
                "Set STANDBYWFI high on cpu3-of-1\n"
                "cpu3-of-1->1-Lvt\n"
                "cluster1->1-0-i\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cluster1->0-0-i\n"
                "Set STANDBYWFI low on cpu0-of-0\n"
                "Set STANDBYWFI low on cpu0-of-1\n"
                "Set STANDBYWFI low on cpu1-of-0\n"
                "Set STANDBYWFI low on cpu1-of-1\n"
                "Set STANDBYWFI low on cpu2-of-0\n"
                "Set STANDBYWFI low on cpu2-of-1\n"
                "Set STANDBYWFI low on cpu3-of-0\n"
                "Set STANDBYWFI low on cpu3-of-1\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            //
            // If we ask for a reset and STANDBYWFI never goes high then we can
            // remove it in the meantime.
            //

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os <<  "About to ask for a pulse reset on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    t.set_cpu_reset_req( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os << "And asking for a rst hold on cpu_reset...\n";
                    // And immediately changing it back should continue to hold the reset
                    t.set_rst_hold_cpu_reset( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os << "Deasserting pulse request on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    t.set_cpu_reset_req( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os << "And deasserting a rst hold on cpu_reset...\n";
                    // And immediately changing it back should continue to hold the reset
                    t.set_rst_hold_cpu_reset( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                os << "About to ask for a pulse reset on cluster" << cluster_index << "\n";
                t.set_cluster_reset_req( cluster_index, true );
                t.print_deltas(os); t.reset_deltas_have_been_processed();
            }

            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                os << "About to deassert a pulse reset on cluster" << cluster_index << "\n";
                t.set_cluster_reset_req( cluster_index, false );
                t.print_deltas(os); t.reset_deltas_have_been_processed();
            }

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "Set STANDBYWFI high on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    // Now to activate the reset then we need to set wfi
                    t.set_wfi_state( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "Set STANDBYWFI low on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    // Now to activate the reset then we need to set wfi
                    t.set_wfi_state( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            ASSERT_SAME(
                os,
                "About to ask for a pulse reset on cpu0-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu0-of-0\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cpu0-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu0-of-1\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cpu1-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu1-of-0\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cpu1-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu1-of-1\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cpu2-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu2-of-0\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cpu2-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu2-of-1\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cpu3-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu3-of-0\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cpu3-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "Deasserting pulse request on cpu3-of-1\n"
                "And deasserting a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cluster0\n"
                "About to ask for a pulse reset on cluster1\n"
                "About to deassert a pulse reset on cluster0\n"
                "About to deassert a pulse reset on cluster1\n"
                "Set STANDBYWFI high on cpu0-of-0\n"
                "Set STANDBYWFI high on cpu0-of-1\n"
                "Set STANDBYWFI high on cpu1-of-0\n"
                "Set STANDBYWFI high on cpu1-of-1\n"
                "Set STANDBYWFI high on cpu2-of-0\n"
                "Set STANDBYWFI high on cpu2-of-1\n"
                "Set STANDBYWFI high on cpu3-of-0\n"
                "Set STANDBYWFI high on cpu3-of-1\n"
                "Set STANDBYWFI low on cpu0-of-0\n"
                "Set STANDBYWFI low on cpu0-of-1\n"
                "Set STANDBYWFI low on cpu1-of-0\n"
                "Set STANDBYWFI low on cpu1-of-1\n"
                "Set STANDBYWFI low on cpu2-of-0\n"
                "Set STANDBYWFI low on cpu2-of-1\n"
                "Set STANDBYWFI low on cpu3-of-0\n"
                "Set STANDBYWFI low on cpu3-of-1\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();

            //
            // Now try the same trick but without deasserting the request and using poreset for
            // variation:
            //

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os <<  "About to ask for a pulse poreset on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    t.set_cpu_poreset_req( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    os << "And asking for a rst hold on cpu_reset...\n";
                    t.set_rst_hold_cpu_reset( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                os << "About to ask for a pulse reset on cluster" << cluster_index << "\n";
                t.set_cluster_reset_req( cluster_index, true );
                t.print_deltas(os); t.reset_deltas_have_been_processed();
            }

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "Set STANDBYWFI high on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    t.set_wfi_state( cpu_id, cluster_index, true );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "Set STANDBYWFI low on cpu" << cpu_id << "-of-" << cluster_index << "\n";
                    t.set_wfi_state( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                {
                    os << "And remove rst hold on cpu_reset...\n";
                    t.set_rst_hold_cpu_reset( cpu_id, cluster_index, false );
                    t.print_deltas(os); t.reset_deltas_have_been_processed();
                }


            ASSERT_SAME(
                os,
                "About to ask for a pulse poreset on cpu0-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse poreset on cpu0-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse poreset on cpu1-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse poreset on cpu1-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse poreset on cpu2-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse poreset on cpu2-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse poreset on cpu3-of-0\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse poreset on cpu3-of-1\n"
                "And asking for a rst hold on cpu_reset...\n"
                "About to ask for a pulse reset on cluster0\n"
                "About to ask for a pulse reset on cluster1\n"
                "Set STANDBYWFI high on cpu0-of-0\n"
                "cpu0-of-0->1-Lvt\n"
                "debug0-of-0->1\n"
                "debug0-of-0->0\n"
                "Set STANDBYWFI high on cpu0-of-1\n"
                "cpu0-of-1->1-Lvt\n"
                "debug0-of-1->1\n"
                "debug0-of-1->0\n"
                "Set STANDBYWFI high on cpu1-of-0\n"
                "cpu1-of-0->1-Lvt\n"
                "debug1-of-0->1\n"
                "debug1-of-0->0\n"
                "Set STANDBYWFI high on cpu1-of-1\n"
                "cpu1-of-1->1-Lvt\n"
                "debug1-of-1->1\n"
                "debug1-of-1->0\n"
                "Set STANDBYWFI high on cpu2-of-0\n"
                "cpu2-of-0->1-Lvt\n"
                "debug2-of-0->1\n"
                "debug2-of-0->0\n"
                "Set STANDBYWFI high on cpu2-of-1\n"
                "cpu2-of-1->1-Lvt\n"
                "debug2-of-1->1\n"
                "debug2-of-1->0\n"
                "Set STANDBYWFI high on cpu3-of-0\n"
                "cpu3-of-0->1-Lvt\n"
                "debug3-of-0->1\n"
                "cluster0->1-0-i\n"
                "debug3-of-0->0\n"
                "cluster0->0-0-i\n"
                "Set STANDBYWFI high on cpu3-of-1\n"
                "cpu3-of-1->1-Lvt\n"
                "debug3-of-1->1\n"
                "cluster1->1-0-i\n"
                "debug3-of-1->0\n"
                "cluster1->0-0-i\n"
                "Set STANDBYWFI low on cpu0-of-0\n"
                "Set STANDBYWFI low on cpu0-of-1\n"
                "Set STANDBYWFI low on cpu1-of-0\n"
                "Set STANDBYWFI low on cpu1-of-1\n"
                "Set STANDBYWFI low on cpu2-of-0\n"
                "Set STANDBYWFI low on cpu2-of-1\n"
                "Set STANDBYWFI low on cpu3-of-0\n"
                "Set STANDBYWFI low on cpu3-of-1\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu0-of-0->0-Lvt\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu0-of-1->0-Lvt\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu1-of-0->0-Lvt\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu1-of-1->0-Lvt\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu2-of-0->0-Lvt\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu2-of-1->0-Lvt\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu3-of-0->0-Lvt\n"
                "And remove rst hold on cpu_reset...\n"
                "cpu3-of-1->0-Lvt\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();
        }

        //
        // Test system reset -- this requires no STANDBYWFI signalling
        //
        t.set_system_reset_req(true);
        t.print_deltas(os);
        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "cpu1-of-0->1-Lvt\n"
            "cpu2-of-0->1-Lvt\n"
            "cpu3-of-0->1-Lvt\n"
            "cpu0-of-1->1-Lvt\n"
            "cpu1-of-1->1-Lvt\n"
            "cpu2-of-1->1-Lvt\n"
            "cpu3-of-1->1-Lvt\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "cpu0-of-0->0-Lvt\n"
            "cpu1-of-0->0-Lvt\n"
            "cpu2-of-0->0-Lvt\n"
            "cpu3-of-0->0-Lvt\n"
            "cpu0-of-1->0-Lvt\n"
            "cpu1-of-1->0-Lvt\n"
            "cpu2-of-1->0-Lvt\n"
            "cpu3-of-1->0-Lvt\n"
            "cluster0->0-0-i\n"
            "cluster1->0-0-i\n"
            "system->0\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();

        //
        // Test system poreset -- this requires no STANDBYWFI signalling
        //
        t.set_poreset_req(true);
        t.print_deltas(os);
        ASSERT_SAME(
            os,
            "cpu0-of-0->1-Lvt\n"
            "debug0-of-0->1\n"
            "cpu1-of-0->1-Lvt\n"
            "debug1-of-0->1\n"
            "cpu2-of-0->1-Lvt\n"
            "debug2-of-0->1\n"
            "cpu3-of-0->1-Lvt\n"
            "debug3-of-0->1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster0->1-0-i\n"
            "cluster1->1-0-i\n"
            "system->1\n"
            "sysdebug->1\n"
            "cpu0-of-0->0-Lvt\n"
            "debug0-of-0->0\n"
            "cpu1-of-0->0-Lvt\n"
            "debug1-of-0->0\n"
            "cpu2-of-0->0-Lvt\n"
            "debug2-of-0->0\n"
            "cpu3-of-0->0-Lvt\n"
            "debug3-of-0->0\n"
            "cpu0-of-1->0-Lvt\n"
            "debug0-of-1->0\n"
            "cpu1-of-1->0-Lvt\n"
            "debug1-of-1->0\n"
            "cpu2-of-1->0-Lvt\n"
            "debug2-of-1->0\n"
            "cpu3-of-1->0-Lvt\n"
            "debug3-of-1->0\n"
            "cluster0->0-0-i\n"
            "cluster1->0-0-i\n"
            "system->0\n"
            "sysdebug->0\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();


        //
        // Do a bit more testing of rst_hold triggering resets.
        //

        for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                os << "Assert STANDBYWFI for cpu" << cpu_id << "-of-" << cluster_index << "\n";
                t.set_wfi_state( cpu_id, cluster_index, true );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();

                os << "Assert rst hold for cpu...\n";
                t.set_rst_hold_cpu_reset( cpu_id, cluster_index, true );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();

                os << "Drop STANDBYWFI...\n";
                t.set_wfi_state( cpu_id, cluster_index, false );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();

                os << "Drop rst hold for cpu...\n";
                t.set_rst_hold_cpu_reset( cpu_id, cluster_index, false );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();

                os << "Now assert rst hold first...\n";
                t.set_rst_hold_cpu_reset( cpu_id, cluster_index, true );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();

                os << "Now assert STANDBYWFI...\n";
                t.set_wfi_state( cpu_id, cluster_index, true );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();

                os << "Drop rst hold now...\n";
                t.set_rst_hold_cpu_reset( cpu_id, cluster_index, false );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();

                os << "Drop STANDBYWFI...\n";
                t.set_wfi_state( cpu_id, cluster_index, false );
                t.print_deltas(os);  t.reset_deltas_have_been_processed();
            }

        ASSERT_SAME(
            os,
            "Assert STANDBYWFI for cpu0-of-0\n"
            "Assert rst hold for cpu...\n"
            "cpu0-of-0->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu0-of-0->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu0-of-0->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu0-of-0->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Assert STANDBYWFI for cpu0-of-1\n"
            "Assert rst hold for cpu...\n"
            "cpu0-of-1->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu0-of-1->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu0-of-1->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu0-of-1->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Assert STANDBYWFI for cpu1-of-0\n"
            "Assert rst hold for cpu...\n"
            "cpu1-of-0->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu1-of-0->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu1-of-0->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu1-of-0->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Assert STANDBYWFI for cpu1-of-1\n"
            "Assert rst hold for cpu...\n"
            "cpu1-of-1->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu1-of-1->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu1-of-1->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu1-of-1->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Assert STANDBYWFI for cpu2-of-0\n"
            "Assert rst hold for cpu...\n"
            "cpu2-of-0->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu2-of-0->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu2-of-0->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu2-of-0->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Assert STANDBYWFI for cpu2-of-1\n"
            "Assert rst hold for cpu...\n"
            "cpu2-of-1->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu2-of-1->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu2-of-1->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu2-of-1->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Assert STANDBYWFI for cpu3-of-0\n"
            "Assert rst hold for cpu...\n"
            "cpu3-of-0->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu3-of-0->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu3-of-0->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu3-of-0->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Assert STANDBYWFI for cpu3-of-1\n"
            "Assert rst hold for cpu...\n"
            "cpu3-of-1->1-Lvt\n"
            "Drop STANDBYWFI...\n"
            "Drop rst hold for cpu...\n"
            "cpu3-of-1->0-Lvt\n"
            "Now assert rst hold first...\n"
            "Now assert STANDBYWFI...\n"
            "cpu3-of-1->1-Lvt\n"
            "Drop rst hold now...\n"
            "cpu3-of-1->0-Lvt\n"
            "Drop STANDBYWFI...\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();

        //
        // Try asserting a cluster reset and a poreset on each
        // core simultaneously
        //

        for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
        {
            unsigned cluster_index = 1;
            os << "About to assert poreset on cpu" << cpu_id << "-of-" << cluster_index << "\n";
            t.set_cpu_poreset_req( cpu_id, cluster_index, true );
            t.print_deltas(os);  t.reset_deltas_have_been_processed();

            os << "About to assert cluster reset on cluster" << cluster_index << "\n";
            t.set_cluster_reset_req( cluster_index, true );
            t.print_deltas(os);  t.reset_deltas_have_been_processed();

        }

        for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
        {
            unsigned cluster_index = 1;
            os << "About to assert STANDBYWFI on cpu" << cpu_id << "-of-" << cluster_index << "\n";
            t.set_wfi_state( cpu_id, cluster_index, true );
            t.print_deltas(os);  t.reset_deltas_have_been_processed();
        }

        for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
        {
            unsigned cluster_index = 1;
            os << "About to deassert STANDBYWFI on cpu" << cpu_id << "-of-" << cluster_index << "\n";
            t.set_wfi_state( cpu_id, cluster_index, true );
            t.print_deltas(os);  t.reset_deltas_have_been_processed();
        }

        ASSERT_SAME(
            os,
            "About to assert poreset on cpu0-of-1\n"
            "About to assert cluster reset on cluster1\n"
            "About to assert poreset on cpu1-of-1\n"
            "About to assert cluster reset on cluster1\n"
            "About to assert poreset on cpu2-of-1\n"
            "About to assert cluster reset on cluster1\n"
            "About to assert poreset on cpu3-of-1\n"
            "About to assert cluster reset on cluster1\n"
            "About to assert STANDBYWFI on cpu0-of-1\n"
            "cpu0-of-1->1-Lvt\n"
            "debug0-of-1->1\n"
            "debug0-of-1->0\n"
            "About to assert STANDBYWFI on cpu1-of-1\n"
            "cpu1-of-1->1-Lvt\n"
            "debug1-of-1->1\n"
            "debug1-of-1->0\n"
            "About to assert STANDBYWFI on cpu2-of-1\n"
            "cpu2-of-1->1-Lvt\n"
            "debug2-of-1->1\n"
            "debug2-of-1->0\n"
            "About to assert STANDBYWFI on cpu3-of-1\n"
            "cpu3-of-1->1-Lvt\n"
            "debug3-of-1->1\n"
            "cluster1->1-0-i\n"
            "cpu0-of-1->0-Lvt\n"
            "cpu1-of-1->0-Lvt\n"
            "cpu2-of-1->0-Lvt\n"
            "cpu3-of-1->0-Lvt\n"
            "debug3-of-1->0\n"
            "cluster1->0-0-i\n"
            "About to deassert STANDBYWFI on cpu0-of-1\n"
            "About to deassert STANDBYWFI on cpu1-of-1\n"
            "About to deassert STANDBYWFI on cpu2-of-1\n"
            "About to deassert STANDBYWFI on cpu3-of-1\n"
            );

        os.str(""); t.reset_deltas_have_been_processed();


        //
        // Check that per cpu configuration is applied correctly.
        //
        {
            cfg_t         last_cfg[MAX_CLUSTERS];

            assert( ! t.are_there_reset_deltasQ() );

            for (unsigned cpu_id = 0; cpu_id != MAX_CORES_PER_CLUSTER; ++ cpu_id)
            {
                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                    last_cfg[ cluster_index ].clear();

                for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
                    for (unsigned cfg = 0; cfg != 9 /* sic */; ++ cfg)
                    {
                        // NOTE the limits of the iteration mean that we put the cfg
                        // back to the original cfg.
                        cfg_t current_cfg;
                        current_cfg.cfgend  = (cfg & 4) != 0;
                        current_cfg.vinithi = (cfg & 2) != 0;
                        current_cfg.teinit  = (cfg & 1) != 0;

                        t.set_cfg( cpu_id, cluster_index,
                                   current_cfg.cfgend,
                                   current_cfg.vinithi,
                                   current_cfg.teinit );
                        assert( ! t.are_there_reset_deltasQ() );
                        assert( current_cfg == t.get_current_cfg( cpu_id, cluster_index ) );
                        assert( ! t.are_there_reset_deltasQ() );
                        assert( last_cfg[ cluster_index ] == t.get_cfg_at_last_reset( cpu_id, cluster_index ) );

                        // Reset only comes into effect when we ask for a reset and it is performed
                        t.set_wfi_state( cpu_id, cluster_index, true );
                        assert( ! t.are_there_reset_deltasQ() );
                        assert( current_cfg == t.get_current_cfg( cpu_id, cluster_index ) );
                        assert( ! t.are_there_reset_deltasQ() );
                        assert( last_cfg[ cluster_index ] == t.get_cfg_at_last_reset( cpu_id, cluster_index ) );

                        t.set_cpu_reset_req( cpu_id, cluster_index, true );
                        assert( current_cfg == t.get_current_cfg( cpu_id, cluster_index ) );
                        assert( current_cfg /*sic*/ == t.get_cfg_at_last_reset( cpu_id, cluster_index ) );

                        t.set_wfi_state( cpu_id, cluster_index, false );

                        t.print_deltas(os); t.reset_deltas_have_been_processed();

                        last_cfg[ cluster_index ] = current_cfg;
                    }
            }

            ASSERT_SAME(
                os,
                "cpu0-of-0->1-Lvt\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu0-of-0->1-LvT\n"
                "cpu0-of-0->0-LvT\n"
                "cpu0-of-0->1-LVt\n"
                "cpu0-of-0->0-LVt\n"
                "cpu0-of-0->1-LVT\n"
                "cpu0-of-0->0-LVT\n"
                "cpu0-of-0->1-Bvt\n"
                "cpu0-of-0->0-Bvt\n"
                "cpu0-of-0->1-BvT\n"
                "cpu0-of-0->0-BvT\n"
                "cpu0-of-0->1-BVt\n"
                "cpu0-of-0->0-BVt\n"
                "cpu0-of-0->1-BVT\n"
                "cpu0-of-0->0-BVT\n"
                "cpu0-of-0->1-Lvt\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu0-of-1->1-Lvt\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu0-of-1->1-LvT\n"
                "cpu0-of-1->0-LvT\n"
                "cpu0-of-1->1-LVt\n"
                "cpu0-of-1->0-LVt\n"
                "cpu0-of-1->1-LVT\n"
                "cpu0-of-1->0-LVT\n"
                "cpu0-of-1->1-Bvt\n"
                "cpu0-of-1->0-Bvt\n"
                "cpu0-of-1->1-BvT\n"
                "cpu0-of-1->0-BvT\n"
                "cpu0-of-1->1-BVt\n"
                "cpu0-of-1->0-BVt\n"
                "cpu0-of-1->1-BVT\n"
                "cpu0-of-1->0-BVT\n"
                "cpu0-of-1->1-Lvt\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu1-of-0->1-LvT\n"
                "cpu1-of-0->0-LvT\n"
                "cpu1-of-0->1-LVt\n"
                "cpu1-of-0->0-LVt\n"
                "cpu1-of-0->1-LVT\n"
                "cpu1-of-0->0-LVT\n"
                "cpu1-of-0->1-Bvt\n"
                "cpu1-of-0->0-Bvt\n"
                "cpu1-of-0->1-BvT\n"
                "cpu1-of-0->0-BvT\n"
                "cpu1-of-0->1-BVt\n"
                "cpu1-of-0->0-BVt\n"
                "cpu1-of-0->1-BVT\n"
                "cpu1-of-0->0-BVT\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu1-of-1->1-LvT\n"
                "cpu1-of-1->0-LvT\n"
                "cpu1-of-1->1-LVt\n"
                "cpu1-of-1->0-LVt\n"
                "cpu1-of-1->1-LVT\n"
                "cpu1-of-1->0-LVT\n"
                "cpu1-of-1->1-Bvt\n"
                "cpu1-of-1->0-Bvt\n"
                "cpu1-of-1->1-BvT\n"
                "cpu1-of-1->0-BvT\n"
                "cpu1-of-1->1-BVt\n"
                "cpu1-of-1->0-BVt\n"
                "cpu1-of-1->1-BVT\n"
                "cpu1-of-1->0-BVT\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu2-of-0->1-LvT\n"
                "cpu2-of-0->0-LvT\n"
                "cpu2-of-0->1-LVt\n"
                "cpu2-of-0->0-LVt\n"
                "cpu2-of-0->1-LVT\n"
                "cpu2-of-0->0-LVT\n"
                "cpu2-of-0->1-Bvt\n"
                "cpu2-of-0->0-Bvt\n"
                "cpu2-of-0->1-BvT\n"
                "cpu2-of-0->0-BvT\n"
                "cpu2-of-0->1-BVt\n"
                "cpu2-of-0->0-BVt\n"
                "cpu2-of-0->1-BVT\n"
                "cpu2-of-0->0-BVT\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu2-of-1->1-LvT\n"
                "cpu2-of-1->0-LvT\n"
                "cpu2-of-1->1-LVt\n"
                "cpu2-of-1->0-LVt\n"
                "cpu2-of-1->1-LVT\n"
                "cpu2-of-1->0-LVT\n"
                "cpu2-of-1->1-Bvt\n"
                "cpu2-of-1->0-Bvt\n"
                "cpu2-of-1->1-BvT\n"
                "cpu2-of-1->0-BvT\n"
                "cpu2-of-1->1-BVt\n"
                "cpu2-of-1->0-BVt\n"
                "cpu2-of-1->1-BVT\n"
                "cpu2-of-1->0-BVT\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-0->1-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cpu3-of-0->1-LvT\n"
                "cpu3-of-0->0-LvT\n"
                "cpu3-of-0->1-LVt\n"
                "cpu3-of-0->0-LVt\n"
                "cpu3-of-0->1-LVT\n"
                "cpu3-of-0->0-LVT\n"
                "cpu3-of-0->1-Bvt\n"
                "cpu3-of-0->0-Bvt\n"
                "cpu3-of-0->1-BvT\n"
                "cpu3-of-0->0-BvT\n"
                "cpu3-of-0->1-BVt\n"
                "cpu3-of-0->0-BVt\n"
                "cpu3-of-0->1-BVT\n"
                "cpu3-of-0->0-BVT\n"
                "cpu3-of-0->1-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cpu3-of-1->1-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cpu3-of-1->1-LvT\n"
                "cpu3-of-1->0-LvT\n"
                "cpu3-of-1->1-LVt\n"
                "cpu3-of-1->0-LVt\n"
                "cpu3-of-1->1-LVT\n"
                "cpu3-of-1->0-LVT\n"
                "cpu3-of-1->1-Bvt\n"
                "cpu3-of-1->0-Bvt\n"
                "cpu3-of-1->1-BvT\n"
                "cpu3-of-1->0-BvT\n"
                "cpu3-of-1->1-BVt\n"
                "cpu3-of-1->0-BVt\n"
                "cpu3-of-1->1-BVT\n"
                "cpu3-of-1->0-BVT\n"
                "cpu3-of-1->1-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();
        }

        {
            cluster_cfg_t         last_cluster_cfg[MAX_CLUSTERS];

            assert( ! t.are_there_reset_deltasQ() );

            for (unsigned cluster_index = 0; cluster_index != MAX_CLUSTERS; ++ cluster_index)
            {
                last_cluster_cfg[ cluster_index ].clear();
                for (unsigned cfg = 0; cfg != 5; ++ cfg)
                {
                    cluster_cfg_t current_cluster_cfg;
                    current_cluster_cfg.cluster_id  = (cfg & 1) != 0 ? 0xa : 0x0;
                    current_cluster_cfg.iminlen     = (cfg & 2) != 0 ? 0xa : 0x0;

                    t.set_cluster_cfg( cluster_index,
                                       current_cluster_cfg.cluster_id,
                                       current_cluster_cfg.iminlen );
                    assert( ! t.are_there_reset_deltasQ() );
                    assert( current_cluster_cfg == t.get_current_cluster_cfg( cluster_index ) );
                    assert( ! t.are_there_reset_deltasQ() );
                    assert( last_cluster_cfg[ cluster_index ] == t.get_cluster_cfg_at_last_reset( cluster_index ) );

                    // Reset only comes into effect when we ask for a reset and it is performed
                    for (unsigned cpu_id = 0; cpu_id != 4; ++ cpu_id)
                        t.set_wfi_state( cpu_id, cluster_index, true );
                    assert( ! t.are_there_reset_deltasQ() );
                    assert( current_cluster_cfg == t.get_current_cluster_cfg( cluster_index ) );
                    assert( ! t.are_there_reset_deltasQ() );
                    assert( last_cluster_cfg[ cluster_index ] == t.get_cluster_cfg_at_last_reset( cluster_index ) );
                    t.set_cluster_reset_req( cluster_index, true );

                    assert( current_cluster_cfg == t.get_current_cluster_cfg( cluster_index ) );
                    assert( current_cluster_cfg /*sic*/ == t.get_cluster_cfg_at_last_reset( cluster_index ) );

                    for (unsigned cpu_id = 0; cpu_id != 4; ++ cpu_id)
                        t.set_wfi_state( cpu_id, cluster_index, false );

                    t.print_deltas(os); t.reset_deltas_have_been_processed();

                    last_cluster_cfg[ cluster_index ] = current_cluster_cfg;
                }
            }

            ASSERT_SAME(
                os,
                "cpu0-of-0->1-Lvt\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu3-of-0->1-Lvt\n"
                "cluster0->1-0-i\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cluster0->0-0-i\n"

                "cpu0-of-0->1-Lvt\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu3-of-0->1-Lvt\n"
                "cluster0->1-10-i\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cluster0->0-10-i\n"

                "cpu0-of-0->1-Lvt\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu3-of-0->1-Lvt\n"
                "cluster0->1-0-I\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cluster0->0-0-I\n"

                "cpu0-of-0->1-Lvt\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu3-of-0->1-Lvt\n"
                "cluster0->1-10-I\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cluster0->0-10-I\n"

                "cpu0-of-0->1-Lvt\n"
                "cpu1-of-0->1-Lvt\n"
                "cpu2-of-0->1-Lvt\n"
                "cpu3-of-0->1-Lvt\n"
                "cluster0->1-0-i\n"
                "cpu0-of-0->0-Lvt\n"
                "cpu1-of-0->0-Lvt\n"
                "cpu2-of-0->0-Lvt\n"
                "cpu3-of-0->0-Lvt\n"
                "cluster0->0-0-i\n"

                "cpu0-of-1->1-Lvt\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu3-of-1->1-Lvt\n"
                "cluster1->1-0-i\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cluster1->0-0-i\n"

                "cpu0-of-1->1-Lvt\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu3-of-1->1-Lvt\n"
                "cluster1->1-10-i\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cluster1->0-10-i\n"

                "cpu0-of-1->1-Lvt\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu3-of-1->1-Lvt\n"
                "cluster1->1-0-I\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cluster1->0-0-I\n"

                "cpu0-of-1->1-Lvt\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu3-of-1->1-Lvt\n"
                "cluster1->1-10-I\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cluster1->0-10-I\n"

                "cpu0-of-1->1-Lvt\n"
                "cpu1-of-1->1-Lvt\n"
                "cpu2-of-1->1-Lvt\n"
                "cpu3-of-1->1-Lvt\n"
                "cluster1->1-0-i\n"
                "cpu0-of-1->0-Lvt\n"
                "cpu1-of-1->0-Lvt\n"
                "cpu2-of-1->0-Lvt\n"
                "cpu3-of-1->0-Lvt\n"
                "cluster1->0-0-i\n"
                );

            os.str(""); t.reset_deltas_have_been_processed();
        }
    }

    void interrupt_generator_t::tests()
    {
        interrupt_generator_t  t;
        std::ostringstream     os;


        t.set_max_number_of_interrupts( 10 ); // choose a small number of interrupts to make testing easier.
        t.reset();

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 0-disabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id0:0\n"
            "        int_id1:0\n"
            "        int_id2:0\n"
            "        int_id3:0\n"
            "        int_id4:0\n"
            "        int_id5:0\n"
            "        int_id6:0\n"
            "        int_id7:0\n"
            "        int_id8:0\n"
            "        int_id9:0\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:   0    0    0    0    0    0    0    0 \n"
            "          8:   0    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        t.write_INT_CTRL(0xFFFF & ~2u);

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    INT_SEQ:-\n"
            "          0:   0    0    0    0    0    0    0    0 \n"
            "          8:   0    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        t.write_INT_GENERATE(0xFFFFfffe); // bit[0] not set so does nothing

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    INT_SEQ:-\n"
            "          0:   0    0    0    0    0    0    0    0 \n"
            "          8:   0    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        t.write_INT_GENERATE(1); // bit[0] set so generate interrupt

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        int_id0:1\n"
            "    INT_SEQ:-\n"
            "          0:(  0)   0    0    0    0    0    0    0 \n"
            "          8:   0    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // We shouldn't write to the INT_SEQ registers whilst running, but
        // we do anyway!
        for (unsigned i = 0; i != 128; ++ i)
        {
            t.write_INT_SEQ( i, 0xFFFFFF80 | (128 - i) );
        }

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    INT_SEQ:-\n"
            "          0:(  0) 127  126  125  124  123  122  121 \n"
            "          8: 120  119 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // But none of these interrupts exist, so generating interrupts should
        // have no effect except for bumping INT_NUMBER!

        t.write_INT_GENERATE(1); // bit[0] set so generate interrupt

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    INT_SEQ:-\n"
            "          0:(  0)(127) 126  125  124  123  122  121 \n"
            "          8: 120  119 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // Now let us exhaust the number of interrupts:
        for (unsigned i = 0; i != 7; ++ i)
            t.write_INT_GENERATE(1); // bit[0] set so generate interrupt

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 9\n"
            "    INT_SEQ:-\n"
            "          0:(  0)(127)(126)(125)(124)(123)(122)(121)\n"
            "          8:(120) 119 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");


        t.write_INT_GENERATE(1); // bit[0] set so generate interrupt

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    INT_SEQ:-\n"
            "          0:(  0)(127)(126)(125)(124)(123)(122)(121)\n"
            "          8:(120)(119)\n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // Further writes have no effect.
        t.write_INT_GENERATE(1); // bit[0] set so generate interrupt

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    INT_SEQ:-\n"
            "          0:(  0)(127)(126)(125)(124)(123)(122)(121)\n"
            "          8:(120)(119)\n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // So now we can ack the interrupts
        t.write_INT_ACK( 0xFFFFfffe ); // do nothing

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    INT_SEQ:-\n"
            "          0:(  0)(127)(126)(125)(124)(123)(122)(121)\n"
            "          8:(120)(119)\n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        t.write_INT_ACK( 1 ); // Actually ack! (But remember all the irq pins are out-of-range

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id0:0\n"
            "    INT_SEQ:-\n"
            "          0:   0  127  126  125  124  123  122  121 \n"
            "          8: 120  119 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // Make sure that if we ack when not all interrupts have fired then we get the right result.
        t.write_INT_GENERATE(1);
        t.write_INT_GENERATE(1);
        t.print(os); t.print_config(os); t.deltas.clear();
        os << "--- ACK\n";
        t.write_INT_ACK(1);
        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        int_id0:1\n"
            "    INT_SEQ:-\n"
            "          0:(  0)(127) 126  125  124  123  122  121 \n"
            "          8: 120  119 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- ACK\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id0:0\n"
            "    INT_SEQ:-\n"
            "          0:   0  127  126  125  124  123  122  121 \n"
            "          8: 120  119 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // And now we program the seq registers to be more useful!

        // We shouldn't write to the INT_SEQ registers whilst running, but
        // we do anyway!
        for (unsigned i = 0; i != 128; ++ i)
        {
            // NOTE first SEQ is 10 which doesn't exists (number of interrupt
            // pins is 10 -- so max id is 9).
            t.write_INT_SEQ( i, 0xFFFFFF80 | (10 - i) );
        }


        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    INT_SEQ:-\n"
            "          0:  10    9    8    7    6    5    4    3 \n"
            "          8:   2    1 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // Now generate some interrupts
        for (unsigned i = 0; i != 10; ++ i)
        {
            t.write_INT_GENERATE(1); t.print(os); t.deltas.clear();
            os << " ---\n";
        }
        t.print_config(os); t.deltas.clear();


        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        int_id9:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        int_id8:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        int_id7:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    Deltas:-\n"
            "        int_id6:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 6\n"
            "    Deltas:-\n"
            "        int_id5:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 7\n"
            "    Deltas:-\n"
            "        int_id4:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 8\n"
            "    Deltas:-\n"
            "        int_id3:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 9\n"
            "    Deltas:-\n"
            "        int_id2:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    Deltas:-\n"
            "        int_id1:1\n"
            " ---\n"
            "    INT_SEQ:-\n"
            "          0:( 10)(  9)(  8)(  7)(  6)(  5)(  4)(  3)\n"
            "          8:(  2)(  1)\n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        t.write_INT_ACK( 1 );

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id1:0\n"
            "        int_id2:0\n"
            "        int_id3:0\n"
            "        int_id4:0\n"
            "        int_id5:0\n"
            "        int_id6:0\n"
            "        int_id7:0\n"
            "        int_id8:0\n"
            "        int_id9:0\n"
            "    INT_SEQ:-\n"
            "          0:  10    9    8    7    6    5    4    3 \n"
            "          8:   2    1 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // We shouldn't write to the INT_SEQ registers whilst running, but
        // we do anyway!
        for (unsigned i = 0; i != 128; ++ i)
        {
            // This time, program all interrupts to be to real pins.
            t.write_INT_SEQ( i, 0xFFFFFF80 | (9 - i) );
        }

        // Now generate some interrupts
        for (unsigned i = 0; i != 10; ++ i)
        {
            t.write_INT_GENERATE(1); t.print(os); t.deltas.clear();
            os << " ---\n";
        }
        t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        int_id9:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        int_id8:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        int_id7:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        int_id6:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    Deltas:-\n"
            "        int_id5:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 6\n"
            "    Deltas:-\n"
            "        int_id4:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 7\n"
            "    Deltas:-\n"
            "        int_id3:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 8\n"
            "    Deltas:-\n"
            "        int_id2:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 9\n"
            "    Deltas:-\n"
            "        int_id1:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    Deltas:-\n"
            "        int_id0:1\n"
            " ---\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)(  3)(  2)\n"
            "          8:(  1)(  0)\n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        // Ack and clear all the interrupts
        t.write_INT_ACK(1);
        t.deltas.clear();


        // Now change the configuration so that we have edge triggered
        // interrupts
        t.write_INT_TYPE( 0, 0xAAAAaaaa );
        t.write_INT_TYPE( 1, 0xAAAAaaaa );
        t.write_INT_TYPE( 2, 0xAAAAaaaa );
        t.write_INT_TYPE( 3, 0xAAAAaaaa );

        t.print_config(os);

        // Now generate some interrupts
        for (unsigned i = 0; i != 10; ++ i)
        {
            t.write_INT_GENERATE(1); t.print(os); t.deltas.clear();
            os << " ---\n";
        }
        t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,

            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: .E.E.E.E   8: .E\n"
            "    INT_TYPE: 000002aa 00000000 00000000 00000000 \n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        int_id9:1\n"
            "        int_id9:0\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        int_id8:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        int_id7:1\n"
            "        int_id7:0\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        int_id6:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    Deltas:-\n"
            "        int_id5:1\n"
            "        int_id5:0\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 6\n"
            "    Deltas:-\n"
            "        int_id4:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 7\n"
            "    Deltas:-\n"
            "        int_id3:1\n"
            "        int_id3:0\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 8\n"
            "    Deltas:-\n"
            "        int_id2:1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 9\n"
            "    Deltas:-\n"
            "        int_id1:1\n"
            "        int_id1:0\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    Deltas:-\n"
            "        int_id0:1\n"
            " ---\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)(  3)(  2)\n"
            "          8:(  1)(  0)\n"
            "    INT_TYPE:-\n"
            "          0: .E.E.E.E   8: .E\n"
            "    INT_TYPE: 000002aa 00000000 00000000 00000000 \n"
            );
        os.str("");

        // Ack and clear all the interrupts
        t.write_INT_ACK(1);

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id0:0\n"
            "        int_id2:0\n"
            "        int_id4:0\n"
            "        int_id6:0\n"
            "        int_id8:0\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: .E.E.E.E   8: .E\n"
            "    INT_TYPE: 000002aa 00000000 00000000 00000000 \n"
            );
        os.str("");

        //
        // It is possible to temporarily disable interrupts using the INT_CTRL bit [0]
        //
        t.print_config(os);

        // Now generate some interrupts
        for (unsigned i = 0; i != 10; ++ i)
        {
            t.write_INT_CTRL( t.read_INT_CTRL() ^ 1 );
            t.write_INT_GENERATE(1); t.print(os); t.deltas.clear();
            os << " ---\n";
        }

        t.print_config(os); t.deltas.clear();

        os << " --- ACK ---\n";
        t.write_INT_ACK(1);

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: .E.E.E.E   8: .E\n"
            "    INT_TYPE: 000002aa 00000000 00000000 00000000 \n"
            "    INT_CTRL: 0-disabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        int_id9:1\n"
            "        int_id9:0\n"
            " ---\n"
            "    INT_CTRL: 0-disabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        int_id8:1\n"
            " ---\n"
            "    INT_CTRL: 0-disabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        int_id7:1\n"
            "        int_id7:0\n"
            " ---\n"
            "    INT_CTRL: 0-disabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        int_id6:1\n"
            " ---\n"
            "    INT_CTRL: 0-disabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            " ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    Deltas:-\n"
            "        int_id5:1\n"
            "        int_id5:0\n"
            " ---\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)   4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: .E.E.E.E   8: .E\n"
            "    INT_TYPE: 000002aa 00000000 00000000 00000000 \n"
            " --- ACK ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id6:0\n"
            "        int_id8:0\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: .E.E.E.E   8: .E\n"
            "    INT_TYPE: 000002aa 00000000 00000000 00000000 \n"
            );
        os.str("");

        //
        // OK this should now have tested most (all?) of the non-timer generated
        // interrupts.
        //

        t.write_INT_TYPE( 0, 0 );
        t.write_INT_TYPE( 1, 0 );
        t.write_INT_TYPE( 2, 0 );
        t.write_INT_TYPE( 3, 0 );

        // Let's enable the timer.
        t.write_INT_CTRL( 0xFFFFffff );

        t.print(os); t.print_config(os); t.deltas.clear();

        for (unsigned i = 0; i != 11; ++ i)
        {
            os << "--- Timer Callback\n";
            t.timer_callback();

            t.print(os); t.print_config(os); t.deltas.clear();
        }

        os << " --- ACK ---\n";
        t.write_INT_ACK(1);

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        int_id9:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)   8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        int_id8:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)   7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        int_id7:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)   6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        int_id6:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)   5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    Deltas:-\n"
            "        int_id5:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)   4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 6\n"
            "    Deltas:-\n"
            "        int_id4:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)   3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 7\n"
            "    Deltas:-\n"
            "        int_id3:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)(  3)   2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 8\n"
            "    Deltas:-\n"
            "        int_id2:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)(  3)(  2)\n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 9\n"
            "    Deltas:-\n"
            "        int_id1:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)(  3)(  2)\n"
            "          8:(  1)   0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    Deltas:-\n"
            "        int_id0:1\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)(  3)(  2)\n"
            "          8:(  1)(  0)\n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 255\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)(  4)(  3)(  2)\n"
            "          8:(  1)(  0)\n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            " --- ACK ---\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id0:0\n"
            "        int_id1:0\n"
            "        int_id2:0\n"
            "        int_id3:0\n"
            "        int_id4:0\n"
            "        int_id5:0\n"
            "        int_id6:0\n"
            "        int_id7:0\n"
            "        int_id8:0\n"
            "        int_id9:0\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");

        //
        // If we disable the timer then we should stop the counter, but we don't
        // know if the timer is capable of being stopped, but we will ignore the
        // callback if it occurs whilst the timers are disabled.
        //

        for (unsigned i = 0; i != 11; ++ i)
        {
            os << "--- Timer enable change\n";
            t.write_INT_CTRL( t.read_INT_CTRL() ^ (1 << 1) );
            t.print(os); t.print_config(os); t.deltas.clear();
            os << "--- Timer Callback\n";
            t.timer_callback();

            t.print(os); t.print_config(os); t.deltas.clear();
        }

        os << " --- ACK ---\n";
        t.write_INT_ACK(1);

        t.print(os); t.print_config(os); t.deltas.clear();

        ASSERT_SAME(
            os,
            "--- Timer enable change\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        int_id9:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)   8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:(  9)   8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)   8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 1\n"
            "    Deltas:-\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)   8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        int_id8:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)   7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)   7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)   7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 2\n"
            "    Deltas:-\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)   7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        int_id7:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)   6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)   6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)   6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 3\n"
            "    Deltas:-\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)   6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        int_id6:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)   5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)   5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)   5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 4\n"
            "    Deltas:-\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)   5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 3-enabled-timer_enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    Deltas:-\n"
            "        int_id5:1\n"
            "        timer@1\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)   4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer enable change\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    Deltas:-\n"
            "        timer-off\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)   4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            "--- Timer Callback\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 5\n"
            "    INT_SEQ:-\n"
            "          0:(  9)(  8)(  7)(  6)(  5)   4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            " --- ACK ---\n"
            "    INT_CTRL: 1-enabled-int_freq:0\n"
            "    INT_NUMBER: 0\n"
            "    Deltas:-\n"
            "        int_id5:0\n"
            "        int_id6:0\n"
            "        int_id7:0\n"
            "        int_id8:0\n"
            "        int_id9:0\n"
            "    INT_SEQ:-\n"
            "          0:   9    8    7    6    5    4    3    2 \n"
            "          8:   1    0 \n"
            "    INT_TYPE:-\n"
            "          0: ........   8: ..\n"
            "    INT_TYPE: 00000000 00000000 00000000 00000000 \n"
            );
        os.str("");
    }
}

#if 1
int main()
{
    DCSCBDetails::interrupt_generator_t::tests();
    DCSCBDetails::reset_handler_t::tests();

    std::cerr << "Test passed OK!" << std::endl;
    return 0;
}
#endif
