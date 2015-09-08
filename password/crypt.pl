#!/usr/bin/perl

use MIME::Base64;

$inFileName = 'ID_PWD';
$outFileName = 'ID_PWD.tmp';

sub encrypt
{
    my ($id, $pwd) = @_;
    open my $in, '<', $inFileName or die "Can't read old file: $!";
    open my $out, '>', $outFileName or die "Can't read old file: $!";
    my $found = 0;
    my $newPwd = encode_base64($pwd);

    while(<$in>)
    {
        if ($_ =~ /^[:blank:]*$id[:blank:]*=/)
        {
            print $out $id . "=" . $newPwd;
            $found = 1;
            next;
        }
        print $out $_;
    }

    if ($found == 0)
    {
        print $out $id . "=" . $newPwd;
    }
    close($in);
    close($out);
    unlink $inFileName;
    rename $outFileName, $inFileName;
}

sub decrypt
{
    my $id = shift;
    open my $in, '<', $inFileName or die "Can't read old file: $!";
    while(<$in>)
    {
        if ($_ =~ /^[:blank:]*$id[:blank:]*=[:blank:]*(.*)[:blank:]*/)
        {
            print decode_base64($1);
            last;
        }
    }
    close($in);
}

sub usage
{
    printf("$0 [[get]|set] <account> [passwd]");
}

$num_args = $#ARGV + 1;

if ($num_args > 3 or $num_args == 0)
{
    usage();
    exit;
}
elsif ($num_args == 3)
{
    if ($ARGV[0] ne 'set')
    {
        usage();
        exit;
    }
    else
    {
        encrypt($ARGV[1], $ARGV[2]);
    }
}
elsif ($num_args == 2)
{
    if ($ARGV[0] ne 'get')
    {
        usage();
        exit;
    }
    else
    {
        decrypt($ARGV[1]);
    }
}
else
{
    decrypt($ARGV[0]);
}
