try
{
    // user code...
}
catch (const AL::ALError& e)
{
    std::cerr << "Caught exception: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
}