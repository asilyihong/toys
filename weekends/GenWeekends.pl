#!/usr/bin/perl

use Time::Local;
my %fixedHoliday = (
    "0101" => "1",
    "0228" => "1",
    "0501" => "1",
    "1010" => "1",
);

sub getWeekends
{
    my $year = shift;
    my $endYear = $year + 1;
    my $dateInfo;
    my $dateString;
    my $dateStr;
    my %holidayHash=();
    my $fileName = sprintf($year . "Weekends.dat");

    $year -= 1;
    $dateInfo = timelocal(0, 0, 0, 15, 11, $year);
    do
    {
        ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime($dateInfo);
        $year += 1900;
        $mon += 1;
        $dateStr = sprintf("%02d%02d", $mon, $mday);
        $dateString = sprintf("%04d%s", $year, $dateStr);
        if ($fixedHoliday{"$dateStr"})
        {
            $holidayHash{"$dateString"} = "1";
        }
        elsif ($wday == 6 or $wday == 0)
        {
            $holidayHash{"$dateString"} = "1";
        }
        $dateInfo += 86400;
    } while ($year != $endYear or $mon != 1 or $mday != 15);
    my $holidayStr = join("\n", sort(keys(%holidayHash)));
    open (FILEFD, '>', $fileName);
    print FILEFD "$holidayStr";
    close(FILEFD);
}

sub usage
{
    printf("$0 [year]\n");
}

$num_args = $#ARGV + 1;
if ($num_args > 1)
{
    usage();
}
elsif ($num_args == 1)
{
    $year = $ARGV[0];
}
else
{
    ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime();
    $year += 1900 + 1; # default for next year
}

getWeekends($year);
