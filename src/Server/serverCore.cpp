/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** serverCore
*/

#include "serverCore.hpp"
#include "tcpConnection.hpp"
#include <boost/filesystem/operations.hpp>


serverCore::serverCore(boost::asio::io_context& ioContext, const std::string& configPath, const std::string& dirPath) :
_acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)), _paths({dirPath ,configPath}), _sigHandler(), _t(ioContext, boost::asio::chrono::seconds(3)), _ctx(boost::asio::ssl::context::sslv23),
_confHandler(_paths)
{
    _modManager.loadLoaders(_confHandler.getListModules());
    boost::filesystem::path p(_paths.configPath);
    if (boost::filesystem::exists(p))
        _lastUpdate = boost::filesystem::last_write_time(p);
    else
        throw ErrorConfigPath();
    _t.async_wait(boost::bind(&serverCore::serverEndHandler, this, _paths.configPath, boost::asio::placeholders::error));
    _ctx.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use);
    // _ctx.set_password_callback(boost::bind(&server::get_password, this));
    _ctx.use_certificate_chain_file(_confHandler.getCertificatePath());
    _ctx.use_private_key_file(_confHandler.getCertificatePath(), boost::asio::ssl::context::pem);
    startAccept();
}

void serverCore::startAccept()
{
    try {
        if (_modManager.doesLoaderExist(moduleType::SSL_MODULE) == true) {
            auto sslMod = _modManager.getNewModule(moduleType::SSL_MODULE);
            if (std::dynamic_pointer_cast<ISocketHandler>(sslMod) != NULL) {
                std::cout << "ssl Creation" << std::endl;
                _sockHandlers.push_back(std::dynamic_pointer_cast<ISocketHandler>(sslMod));
            }
        } else {
            std::cout << "tcp Creation" << std::endl;
            _sockHandlers.push_back(std::make_shared<tcpConnection>());
        }
        _sockHandlers.back()->prepareSocketHandler(_acceptor.get_executor().context(), _modManager, _ctx);
        _sockHandlers.back()->reload(_confHandler.getListModules(), _confHandler.getCgiPath(), _confHandler.getCopyProcessList());
        _acceptor.async_accept(_sockHandlers.back()->getSocket(), boost::bind(&serverCore::handleAccept, 
        this, _sockHandlers.back(),boost::asio::placeholders::error));
    } catch (Error& e) {
        std::cout << "Fail to connect because " << e.what() << std::endl;
        _acceptor.async_wait(
        boost::asio::ip::tcp::acceptor::wait_read,
        boost::bind(&serverCore::startAccept, this));
    }
}

void serverCore::handleAccept(std::shared_ptr<ISocketHandler>& newConnection, const boost::system::error_code& error)
{
    if (!error)
    {
        try {
            newConnection->start();
        } catch (Error& e) {
            std::cout << e.what() << std::endl;
        }
    }
    startAccept();
}

void serverCore::start()
{
    _acceptor.get_io_service().run();
}

void serverCore::serverEndHandler(const std::string& configPath, const boost::system::error_code& err)
{
    if (err)
        return;
    boost::filesystem::path p(configPath);
    if (boost::filesystem::exists(p)) {
        if (_lastUpdate != boost::filesystem::last_write_time(p)) {
            _confHandler.reload();
            for (auto& sock : _sockHandlers) 
                sock->reload(_confHandler.getListModules(), _confHandler.getCgiPath(), _confHandler.getCopyProcessList());
            // if (_modManager.doesModuleExist(moduleType::PHPCGI))
            //     _modManager.getModule(moduleType::PHPCGI)->init(_confHandler.getCgiPath());
            // if (_reqManager.doesModuleExist(moduleType::SSL_MODULE))
            //     _reqManager.getModule(moduleType::SSL_MODULE)->init(_confHandler.getCertificatePath(), _socket);
            _lastUpdate = boost::filesystem::last_write_time(p);
        }
    } else
        throw ErrorConfigPath();
    if (_sigHandler.isInterrupted() == true) {
        std::cerr << "Server's leaving." << std::endl;
        stop();
    }
    _t.expires_at(_t.expires_at() + boost::asio::chrono::seconds(3));
    _t.async_wait(boost::bind(&serverCore::serverEndHandler, this, configPath, boost::asio::placeholders::error));
}

void serverCore::stop()
{
    if (_acceptor.is_open() == true)
        _acceptor.get_io_service().stop();
}